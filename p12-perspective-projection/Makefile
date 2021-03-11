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

# trans
TRANS_O=$(OBJ_DIR)trans.o
TRANS_CPP=$(SRC_DIR)trans.cpp

# persp
PERSP_O=$(OBJ_DIR)persp.o
PERSP_CPP=$(SRC_DIR)persp.cpp

$(MAIN_X): $(MAIN_O) $(TRANS_O) $(PERSP_O)
	g++ -o $(MAIN_X) $(MAIN_O) $(TRANS_O) $(PERSP_O) $(LDLIBS)

$(MAIN_O): $(MAIN_CPP)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

$(TRANS_O): $(TRANS_CPP)
	g++ -c $(TRANS_CPP) -o $(TRANS_O)

$(PERSP_O): $(PERSP_CPP)
	g++ -c $(PERSP_CPP) -o $(PERSP_O)

clean:
	rm -f $(ALL_EXE) $(ALL_OBJ)
