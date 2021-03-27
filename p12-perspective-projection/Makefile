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

$(MAIN_X): $(MAIN_O) $(TRANS_O) $(PERSP_O)
	g++ -o $(MAIN_X) $(MAIN_O) $(TRANS_O) $(PERSP_O) $(LDLIBS)

$(MAIN_O): $(MAIN_CPP) $(MAIN_HPP)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

$(TRANS_O): $(TRANS_CPP) $(TRANS_HPP)
	g++ -c $(TRANS_CPP) -o $(TRANS_O)

$(PERSP_O): $(PERSP_CPP) $(PERSP_HPP)
	g++ -c $(PERSP_CPP) -o $(PERSP_O)

clean:
	rm -f $(ALL_EXE) $(ALL_OBJ)
