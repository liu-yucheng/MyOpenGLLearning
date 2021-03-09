EXE_DIR=./
OBJ_DIR=./
SRC_DIR=./

LDLIBS=-lGL -lglut -lGLEW

ALL_EXE=$(EXE_DIR)*.x
ALL_OBJ=$(OBJ_DIR)*.o

MAIN_X=$(EXE_DIR)main.x
MAIN_O=$(OBJ_DIR)main.o
MAIN_CPP=$(SRC_DIR)main.cpp

$(MAIN_X): $(MAIN_O)
	g++ -o $(MAIN_X) $(MAIN_O) $(LDLIBS)

$(MAIN_O): $(MAIN_CPP)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

clean:
	rm -f $(ALL_EXE) $(ALL_OBJ)
