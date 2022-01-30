# Copyright 2022 Yucheng Liu. GNU GPL3 license.
# GNU GPL3 license copy: https://www.gnu.org/licenses/gpl-3.0.txt

EXE_DIR=./
OBJ_DIR=./
SRC_DIR=./

LDLIBS=-lGL -lglut -lGLEW

ALL_EXE=$(EXE_DIR)*.x
ALL_OBJ=$(OBJ_DIR)*.o

# main
MAIN_X=$(EXE_DIR)main.x
MAIN_O=$(OBJ_DIR)main.o
MAIN_CPP=$(SRC_DIR)main.cpp
MAIN_SRC=$(MAIN_CPP) $(SRC_DIR)main.hpp

# trans
TRANS_O=$(OBJ_DIR)trans.o
TRANS_CPP=$(SRC_DIR)trans.cpp
TRANS_SRC=$(TRANS_CPP) $(SRC_DIR)trans.hpp

# persp
PERSP_O=$(OBJ_DIR)persp.o
PERSP_CPP=$(SRC_DIR)persp.cpp
PERSP_SRC=$(PERSP_CPP) $(SRC_DIR)persp.hpp

# cam
CAM_O=$(OBJ_DIR)cam.o
CAM_CPP=$(SRC_DIR)cam.cpp
CAM_SRC=$(CAM_CPP) $(SRC_DIR)cam.hpp

# pipeline
PIPELINE_O=$(OBJ_DIR)pipeline.o
PIPELINE_CPP=$(SRC_DIR)pipeline.cpp
PIPELINE_SRC=$(PIPELINE_CPP) $(SRC_DIR)pipeline.hpp

$(MAIN_X): $(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O) $(PIPELINE_O)
	g++ -o $(MAIN_X) \
	    $(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O) $(PIPELINE_O) \
	    $(LDLIBS)

$(MAIN_O): $(MAIN_SRC)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

$(TRANS_O): $(TRANS_SRC)
	g++ -c $(TRANS_CPP) -o $(TRANS_O)

$(PERSP_O): $(PERSP_SRC)
	g++ -c $(PERSP_CPP) -o $(PERSP_O)

$(CAM_O): $(CAM_SRC)
	g++ -c $(CAM_CPP) -o $(CAM_O)

$(PIPELINE_O): $(PIPELINE_SRC) $(TRANS_SRC) $(PERSP_SRC) $(CAM_SRC)
	g++ -c $(PIPELINE_CPP) -o $(PIPELINE_O)

clean:
	rm -f $(ALL_EXE) $(ALL_OBJ)
