EXE_DIR=./
OBJ_DIR=./
SRC_DIR=./
LDLIBS=-lglut -lGLU -lGL

$(EXE_DIR)main.x: $(OBJ_DIR)main.o
	g++ -o $(EXE_DIR)main.x $(OBJ_DIR)main.o $(LDLIBS)

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp
	g++ -c $(SRC_DIR)main.cpp -o $(OBJ_DIR)main.o $(LDLIBS)
