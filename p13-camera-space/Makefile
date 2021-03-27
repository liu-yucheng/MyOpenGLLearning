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
MAIN_HPP=$(SRC_DIR)main.hpp

# trans
TRANS_O=$(OBJ_DIR)trans.o
TRANS_CPP=$(SRC_DIR)trans.cpp
TRANS_HPP=$(SRC_DIR)trans.hpp

# persp
PERSP_O=$(OBJ_DIR)persp.o
PERSP_CPP=$(SRC_DIR)persp.cpp
PERSP_HPP=$(SRC_DIR)persp.hpp

# cam
CAM_O=$(OBJ_DIR)cam.o
CAM_CPP=$(SRC_DIR)cam.cpp
CAM_HPP=$(SRC_DIR)cam.hpp

# Objects to link
TO_LINK=$(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O)

$(MAIN_X): $(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O)
	g++ -o $(MAIN_X) $(TO_LINK) $(LDLIBS)

$(MAIN_O): $(MAIN_CPP) $(MAIN_HPP)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

$(TRANS_O): $(TRANS_CPP) $(TRANS_HPP)
	g++ -c $(TRANS_CPP) -o $(TRANS_O)

$(PERSP_O): $(PERSP_CPP) $(PERSP_HPP)
	g++ -c $(PERSP_CPP) -o $(PERSP_O)

$(CAM_O): $(CAM_CPP) $(CAM_HPP)
	g++ -c $(CAM_CPP) -o $(CAM_O)

clean:
	rm -f $(ALL_EXE) $(ALL_OBJ)
