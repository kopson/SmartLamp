DEBUG ?= 1

CFLAGS := -std=c++11

ifeq ($(DEBUG), 1)
    CFLAGS += -g3 -DDEBUG
else
    CFLAGS += -DNDEBUG
endif

CXX = g++ $(CFLAGS)

SRC_DIR := src/
SRCT_DIR := test/
OBJ_DIR := obj/
OUT_DIR := out/
OUT_O_DIR := $(OUT_DIR)$(OBJ_DIR)

CPP_FILES := $(wildcard $(SRC_DIR)*.cpp)
OBJ_FILES := $(addprefix $(OUT_O_DIR),$(notdir $(CPP_FILES:.cpp=.o)))
CPPT_FILES := $(wildcard $(SRCT_DIR)*.cpp)
OBJT_FILES := $(addprefix $(OUT_O_DIR),$(notdir $(CPPT_FILES:.cpp=.o)))
OBJT_FILES += $(OBJ_FILES)
OBJT_FILES := $(filter-out $(OUT_O_DIR)Main.o, $(OBJT_FILES))

LD_FLAGS := -L/home/piotrek/workspace/CPP/lib
CC_FLAGS := -MMD
INCLUDES := inc/

all: dirs main utest

default: main

dirs:
	mkdir -p $(OUT_O_DIR)

main: $(OBJ_FILES)
	$(CXX) $(LD_FLAGS) -o $(OUT_DIR)$@ $^

$(OUT_O_DIR)%.o: $(SRC_DIR)%.cpp
	$(CXX) -Wall $(CC_FLAGS) -I$(INCLUDES) -c -o $@ $<

utest: $(OBJT_FILES)
	$(CXX) $(LD_FLAGS) -o $(OUT_DIR)$@ $^ -lcpptest

$(OUT_O_DIR)%.o: $(SRCT_DIR)%.cpp
	$(CXX) -Wall $(CC_FLAGS) -I$(INCLUDES) -c -o $@ $<

clean:
	rm -rf $(OUT_DIR)