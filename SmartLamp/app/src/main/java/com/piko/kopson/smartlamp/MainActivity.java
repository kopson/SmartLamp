package com.piko.kopson.smartlamp;

import android.content.Context;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.view.MenuItemCompat;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import com.kyleduo.switchbutton.SwitchButton;

import org.achartengine.ChartFactory;
import org.achartengine.GraphicalView;
import org.achartengine.chart.BarChart;
import org.achartengine.chart.PointStyle;
import org.achartengine.model.RangeCategorySeries;
import org.achartengine.model.XYMultipleSeriesDataset;
import org.achartengine.model.XYSeries;
import org.achartengine.renderer.XYMultipleSeriesRenderer;
import org.achartengine.renderer.XYSeriesRenderer;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.URI;
import java.net.URISyntaxException;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    // Instance of the progress action-view
    MenuItem miActionProgressItem;

    private static final String READ_PIN_PARAM  = "RPIN";
    private static final String WRITE_PIN_PARAM = "WPIN";
    private static final int    LED_SECTIONS    = 3;

    private SeekBar[] seek;
    private TextView[] text;

    private LinearLayout chartLyt;
    private Animation fadeAnim;

    private TextView temp1;
    private TextView temp2;

    private AsyncTask recentTask = null;
    private int[] recentProgress;
    private Map<Integer, Integer> idMap;
    private String PACKAGE_NAME;

    private String serverResponse = "ERROR";

    private XYSeries[] series;
    private static int histSize = 30;
    private boolean histGraph = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        seek = new SeekBar[LED_SECTIONS];
        text = new TextView[LED_SECTIONS];
        idMap = new HashMap<>();
        series = new XYSeries[2];

        series[0] = new XYSeries(getResources().getString(R.string.water_temp));
        series[1] = new XYSeries(getResources().getString(R.string.lamp_temp));

        Switch[] switchButton = new Switch[LED_SECTIONS];
        recentProgress = new int[LED_SECTIONS];

        PACKAGE_NAME = getApplicationContext().getPackageName();
        String viewId;
        int resID;

        for(int i = 1; i <= LED_SECTIONS; i++) {
            viewId = "section_bar_" + i;
            resID = getResources().getIdentifier(viewId, "id", PACKAGE_NAME);
            seek[i - 1] = (SeekBar) findViewById(resID);
            idMap.put(seek[i - 1].getId(), i);
            seek[i - 1].setEnabled(false);
            seek[i - 1].setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {

                @Override
                public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                    int id = idMap.get(seekBar.getId());

                    int resID = getResources().getIdentifier("LED_PIN_" + id, "string", PACKAGE_NAME);
                    if (!httpRequest(WRITE_PIN_PARAM, getResources().getString(resID))) {
                        seekBar.setProgress(recentProgress[id - 1]);
                        return;
                    }
                    recentProgress[id - 1] = progress;
                    text[id - 1].setText(progress + " %");
                }

                @Override
                public void onStartTrackingTouch(SeekBar seekBar) {

                }

                @Override
                public void onStopTrackingTouch(SeekBar seekBar) {

                }
            });

            viewId = "section_txt_" + i;
            resID = getResources().getIdentifier(viewId, "id", PACKAGE_NAME);
            text[i - 1] = (TextView) findViewById(resID);
            idMap.put(text[i - 1].getId(), i);

            viewId = "section_" + i;
            resID = getResources().getIdentifier(viewId, "id", PACKAGE_NAME);
            switchButton[i - 1] = (Switch) findViewById(resID);
            idMap.put(switchButton[i - 1].getId(), i);
            switchButton[i - 1].setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {

                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
                    int id = idMap.get(buttonView.getId());
                    int resID = getResources().getIdentifier("LED_PIN_" + id, "string", PACKAGE_NAME);

                    if(!httpRequest(WRITE_PIN_PARAM, getResources().getString(resID))) {
                        buttonView.setChecked(false);
                        return;
                    }

                    seek[id - 1].setEnabled(isChecked);
                }
            });
        }

        temp1 = (TextView) findViewById(R.id.temp_1);
        temp2 = (TextView) findViewById(R.id.temp_4);

        ImageView fan = (ImageView) findViewById(R.id.imageView);
        SwitchButton cooler = (SwitchButton) findViewById(R.id.cooler);

        final Animation rotation = AnimationUtils.loadAnimation(MainActivity.this, R.anim.rotation);
        fan.setAnimation(rotation);
        rotation.cancel();

        cooler.setOnCheckedChangeListener(new SwitchButton.OnCheckedChangeListener() {

            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {

                //if (!httpRequest(WRITE_PIN_PARAM, getResources().getString(R.string.COOLER_PIN)))
                //    cooler.setChecked(false);
                if (isChecked) {
                    rotation.reset();
                    rotation.start();
                } else {
                    rotation.cancel();
                }
            }
        });

        chartLyt = (LinearLayout) findViewById(R.id.graph_layout);
        chartLyt.addView(createTempGraph(), 0);
        fadeAnim = AnimationUtils.loadAnimation(this, R.anim.fade_anim);

        Thread thread = new Thread() {
            @Override
            public void run() {
                try {
                    int xVal = 0;
                    while(true) {
                        if(!histGraph)
                            updateTempGraph(xVal++ % histSize);
                        sleep(1000);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        };

        thread.start();
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.menu.activity_main, menu);
        return true;
    }

    @Override
    public boolean onPrepareOptionsMenu(Menu menu) {
        // Store instance of the menu item containing progress
        miActionProgressItem = menu.findItem(R.id.miActionProgress);
        // Extract the action-view from the menu item
        ProgressBar v =  (ProgressBar) MenuItemCompat.getActionView(miActionProgressItem);
        // Return to finish
        return super.onPrepareOptionsMenu(menu);
    }

    public void showProgressBar() {
        // Show progress item
        miActionProgressItem.setVisible(true);
    }

    public void hideProgressBar() {
        // Hide progress item
        miActionProgressItem.setVisible(false);
    }

    private XYSeriesRenderer createRenderer(int c) {

        // Now we create the renderer
        XYSeriesRenderer renderer = new XYSeriesRenderer();
        renderer.setLineWidth(2);
        renderer.setColor(c);
        // Include low and max value
        renderer.setDisplayBoundingPoints(true);
        // we add point markers
        renderer.setPointStyle(PointStyle.CIRCLE);
        renderer.setPointStrokeWidth(3);

        renderer.setDisplayChartValues(true);
        renderer.setChartValuesTextSize(22);
        renderer.setAnnotationsTextSize(22);

        NumberFormat format = NumberFormat.getNumberInstance();
        format.setMaximumFractionDigits(2);
        renderer.setChartValuesFormat(format);

        return renderer;
    }

    private void updateTempGraph(int i) {

        Random r = new Random();
        final double r1 = 20.0 + r.nextDouble() % 6.0;
        final double r2 = 10.0 + r.nextDouble() % 2.0;

        if(series[0].getItemCount() >= histSize) {

            for(int j = 0; j < histSize - 1; ++j) {
                double atJ0 = series[0].getY(j+1);
                double atJ1 = series[1].getY(j+1);

                series[0].remove(j);
                series[1].remove(j);

                series[0].add(j, j, atJ0);
                series[1].add(j, j, atJ1);
            }
            series[0].remove(histSize - 1);
            series[1].remove(histSize - 1);
            series[0].add(histSize - 1, histSize - 1, r1);
            series[1].add(histSize - 1, histSize - 1, r2);
        } else {
            series[0].add(i, i, r1);
            series[1].add(i, i, r2);
        }
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                DecimalFormat df = new DecimalFormat("##.00");
                temp1.setText(df.format(r1));
                temp2.setText(df.format(r2));
                chartLyt.removeViewAt(0);
                chartLyt.addView(createTempGraph(), 0);
            }
        });
    }

    /**
     * Builds a bar multiple series renderer to use the provided colors.
     *
     * @param colors the series renderers colors
     * @return the bar multiple series renderer
     */
    protected XYMultipleSeriesRenderer buildBarRenderer(int[] colors) {
        XYMultipleSeriesRenderer renderer = new XYMultipleSeriesRenderer();
        renderer.setAxisTitleTextSize(16);
        renderer.setChartTitleTextSize(20);
        renderer.setLabelsTextSize(16);
        renderer.setLegendTextSize(18);
        renderer.setYLabelsPadding(10);

        for (int color : colors) {
            XYSeriesRenderer r = new XYSeriesRenderer();
            r.setColor(color);
            renderer.addSeriesRenderer(r);
        }
        return renderer;
    }

    /**
     * Sets a few of the series renderer settings.
     *
     * @param renderer the renderer to set the properties to
     * @param title the chart title
     * @param xMin the minimum value on the X axis
     * @param xMax the maximum value on the X axis
     * @param yMin the minimum value on the Y axis
     * @param yMax the maximum value on the Y axis
     * @param axesColor the axes color
     * @param labelsColor the labels color
     */
    protected void setChartSettings(XYMultipleSeriesRenderer renderer, String title, double xMin,
                                    double xMax, double yMin, double yMax, int axesColor,
                                    int labelsColor) {
        renderer.setChartTitle(title);
        renderer.setXAxisMin(xMin);
        renderer.setXAxisMax(xMax);
        renderer.setYAxisMin(yMin);
        renderer.setYAxisMax(yMax);
        renderer.setAxesColor(axesColor);
        renderer.setLabelsColor(labelsColor);
    }

    private View createHistGraph() {
        double[] minValues = new double[] { -24, -19, -10, -1, 7, 12, 15, 14, 9, 1, -11, -16 };
        double[] maxValues = new double[] { 7, 12, 24, 28, 33, 35, 37, 36, 28, 19, 11, 4 };

        XYMultipleSeriesDataset dataset = new XYMultipleSeriesDataset();
        RangeCategorySeries series = new RangeCategorySeries("Temperatura wody");
        int length = minValues.length;
        for (int k = 0; k < length; k++) {
            series.add(minValues[k], maxValues[k]);
        }
        dataset.addSeries(series.toXYSeries());
        int[] colors = new int[] { Color.RED };
        XYMultipleSeriesRenderer renderer = buildBarRenderer(colors);
        setChartSettings(renderer, "Godzinowe zmiany temperatury", 0.5, 12.5,
                -30, 45, Color.GRAY, Color.LTGRAY);
        renderer.setBarSpacing(0.5);
        renderer.setYLabelsAlign(Paint.Align.RIGHT);
        renderer.setMarginsColor(Color.argb(0x00, 0xff, 0x00, 0x00)); // transparent margins

        XYSeriesRenderer r = (XYSeriesRenderer) renderer.getSeriesRendererAt(0);
        r.setDisplayChartValues(true);
        r.setChartValuesTextSize(22);
        r.setChartValuesSpacing(3);
        r.setGradientEnabled(true);
        r.setGradientStart(-20, Color.BLUE);
        r.setGradientStop(20, Color.GREEN);

        GraphicalView chartView = ChartFactory.getRangeBarChartView(this, dataset, renderer, BarChart.Type.DEFAULT);

        // Enable chart click
        renderer.setClickEnabled(true);
        chartView.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                applyAnim(v, createTempGraph());
                histGraph = false;
            }
        });

        return chartView;
    }

    private View createTempGraph() {

        XYSeriesRenderer[] renderers = {
                createRenderer(Color.RED),
                createRenderer(Color.DKGRAY)
        };

        // Now we add our series
        XYMultipleSeriesDataset dataset = new XYMultipleSeriesDataset();
        for(XYSeries ser : series) {
            dataset.addSeries(ser);
        }

        XYMultipleSeriesRenderer mRenderer = new XYMultipleSeriesRenderer();
        for(XYSeriesRenderer ren : renderers) {
            mRenderer.addSeriesRenderer(ren);
        }

        // We want to avoid black border
        mRenderer.setMarginsColor(Color.argb(0x00, 0xff, 0x00, 0x00)); // transparent margins
        // Disable Pan on two axis
        mRenderer.setPanEnabled(false, false);
        mRenderer.setYAxisMax(30);
        mRenderer.setYAxisMin(0);
        mRenderer.setShowGrid(true); // we show the grid
        mRenderer.setAxisTitleTextSize(16);
        mRenderer.setChartTitleTextSize(20);
        mRenderer.setLabelsTextSize(16);
        mRenderer.setLegendTextSize(18);
        mRenderer.setYLabelsAlign(Paint.Align.RIGHT);
        mRenderer.setYLabelsPadding(10);
        mRenderer.setChartTitle("Historia temperatur");

        GraphicalView chartView = ChartFactory.getLineChartView(this, dataset, mRenderer);

        // Enable chart click
        mRenderer.setClickEnabled(true);
        chartView.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                applyAnim(v, createHistGraph());
                histGraph = true;
            }
        });
        return chartView;
    }

    private void applyAnim(final View v, final View nextView) {

        Animation.AnimationListener list = new Animation.AnimationListener() {

            @Override
            public void onAnimationStart(Animation animation) {

            }

            @Override
            public void onAnimationEnd(Animation animation) {

                chartLyt.removeViewAt(0);
                chartLyt.addView(nextView,0);
            }

            @Override
            public void onAnimationRepeat(Animation animation) {

            }
        };

        fadeAnim.setAnimationListener(list);
        v.startAnimation(fadeAnim);
    }

    private boolean httpRequest(String parameterName, String parameterValue) {

        if(recentTask != null && recentTask.getStatus() != AsyncTask.Status.FINISHED) {
            Toast.makeText(this, "Task not finished: " + recentTask.getStatus().name(),
                    Toast.LENGTH_SHORT).show();
            Log.v(TAG, "Task status: " + recentTask.getStatus().name());
            return false;
        }

        Log.v(TAG, "Task param: " + parameterName + " value: " + parameterValue + " status: " + recentTask);
        recentTask = new HttpRequestAsyncTask(this, parameterName, parameterValue).execute();
        return recentTask != null &&  serverResponse.equals("OK");
    }

    /**
     * Description: Send an HTTP Get request to a specified ip address and port.
     * Also send a parameter "parameterName" with the value of "parameterValue".
     * @param parameterName parameter name
     * @param parameterValue the pin number to toggle
     * @return The ip address' reply text, or an ERROR message is it fails to receive one
     */
    public String sendRequest(String parameterName, String parameterValue) {

        try {
            HttpClient httpclient = new DefaultHttpClient(); // create an HTTP client
            String ipAddress = getResources().getString(R.string.ip_address);
            String portNumber =  getResources().getString(R.string.port_number);
            URI website = new URI("http://" + ipAddress + ":" + portNumber + "/?" + parameterName +
                    "=" + parameterValue);
            HttpGet getRequest = new HttpGet(); // create an HTTP GET object
            getRequest.setURI(website); // set the URL of the GET request
            HttpResponse response = httpclient.execute(getRequest); // execute the request

            // get the ip address server's reply
            InputStream content = null;
            content = response.getEntity().getContent();
            BufferedReader in = new BufferedReader(new InputStreamReader(content));
            serverResponse = in.readLine();

            // Close the connection
            content.close();
        } catch (ClientProtocolException e) {
            // HTTP error
            serverResponse = e.getMessage();
            e.printStackTrace();
        } catch (IOException e) {
            // IO error
            serverResponse = e.getMessage();
            e.printStackTrace();
        } catch (URISyntaxException e) {
            // URL syntax error
            serverResponse = e.getMessage();
            e.printStackTrace();
        }

        // return the server's reply/response text
        return serverResponse;
    }

    /**
     * An AsyncTask is needed to execute HTTP requests in the background so that they do not
     * block the user interface.
     */
    private class HttpRequestAsyncTask extends AsyncTask<Void, Void, Void> {

        // declare variables needed
        private String requestReply;
        private String parameter;
        private String parameterValue;
        private Context context;

        /**
         * Description: The asyncTask class constructor. Assigns the values used in its other methods.
         * @param parameter the parameter name
         * @param parameterValue the pin number to toggle
         */
        public HttpRequestAsyncTask(Context context, String parameter, String parameterValue)
        {
            this.context = context;
            this.parameterValue = parameterValue;
            this.parameter = parameter;
        }

        /**
         * Name: doInBackground
         * Description: Sends the request to the ip address
         * @param voids params
         * @return null
         */
        @Override
        protected Void doInBackground(Void... voids) {

            requestReply = sendRequest(parameter, parameterValue);
            return null;
        }

        /**
         * Name: onPostExecute
         * Description: This function is executed after the HTTP request returns from the ip address.
         * The function sets the dialog's message with the reply text from the server and display the dialog
         * if it's not displayed already (in case it was closed by accident);
         * @param aVoid void parameter
         */
        @Override
        protected void onPostExecute(Void aVoid) {
            hideProgressBar();
            Toast.makeText(context, "Server Response: " + requestReply, Toast.LENGTH_SHORT).show();
        }

        /**
         * Name: onPreExecute
         * Description: This function is executed before the HTTP request is sent to ip address.
         * The function will set the dialog's message and display the dialog.
         */
        @Override
        protected void onPreExecute() {

            showProgressBar();
        }
    }
}
