
void setup() {
  Serial.begin(9600);
}

#define NUM_READS 100

float readTemperature(int sensorpin) {
   // read multiple values and sort them to take the mode
   int sortedValues[NUM_READS];
   
   for(int i = 0; i < NUM_READS; i++) {
     int value = analogRead(sensorpin);
     int j;
     if(value < sortedValues[0] || i == 0) {
        j = 0; //insert at first position
     } else {
       for(j = 1; j < i; j++) {
          if(sortedValues[j - 1] <= value && sortedValues[j] >= value) {
            // j is insert position
            break;
          }
       }
     }
     for(int k = i; k > j; k--) {
       // move all values higher than current reading up one position
       sortedValues[k] = sortedValues[k - 1];
     }
     sortedValues[j] = value; //insert current reading
   }
   //return scaled mode of 10 values
   float returnval = 0;
   for(int i = NUM_READS / 2 - 5; i < (NUM_READS / 2 + 5); i++) {
     returnval += sortedValues[i];
   }
   returnval = returnval / 10;
   return returnval * 1100 / 1023;
}

void loop() {
  int value = analogRead(A3);
  Serial.print("Raw: ");
  Serial.print(value);
  Serial.print(" Avg: ");
  Serial.println(readTemperature(A3));
  delay(50);
}
