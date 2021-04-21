# Directories.
EXE_D=./
OBJ_D=./obj/
SRC_D=./src/
DIRS=$(EXE_D) $(OBJ_D) $(SRC_D)

# Link dynamic libraries flags.
LDLIBS=-lGL -lglut -lGLEW

# File sets by extensions.
EXES=$(EXE_D)*.x
OBJS=$(OBJ_D)*.o

# main
MAIN_X=$(EXE_D)main.x
MAIN_O=$(OBJ_D)main.o
MAIN_CPP=$(SRC_D)main.cpp
MAIN_HPP=$(SRC_D)main.hpp

# trans
TRANS_O=$(OBJ_D)trans.o
TRANS_CPP=$(SRC_D)trans.cpp
TRANS_HPP=$(SRC_D)trans.hpp

# persp
PERSP_O=$(OBJ_D)persp.o
PERSP_CPP=$(SRC_D)persp.cpp
PERSP_HPP=$(SRC_D)persp.hpp

# cam
CAM_O=$(OBJ_D)cam.o
CAM_CPP=$(SRC_D)cam.cpp
CAM_HPP=$(SRC_D)cam.hpp

# pipeline
PIPELINE_O=$(OBJ_D)pipeline.o
PIPELINE_CPP=$(SRC_D)pipeline.cpp
PIPELINE_HPP=$(SRC_D)pipeline.hpp

$(MAIN_X): $(DIRS) $(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O) $(PIPELINE_O)
	g++ -o $(MAIN_X) \
	    $(MAIN_O) $(TRANS_O) $(PERSP_O) $(CAM_O) $(PIPELINE_O) \
	    $(LDLIBS)

$(MAIN_O): $(MAIN_CPP) $(MAIN_HPP)
	g++ -c $(MAIN_CPP) -o $(MAIN_O)

$(TRANS_O): $(TRANS_CPP) $(TRANS_HPP)
	g++ -c $(TRANS_CPP) -o $(TRANS_O)

$(PERSP_O): $(PERSP_CPP) $(PERSP_HPP)
	g++ -c $(PERSP_CPP) -o $(PERSP_O)

$(CAM_O): $(CAM_CPP) $(CAM_HPP)
	g++ -c $(CAM_CPP) -o $(CAM_O)

$(PIPELINE_O): $(PIPELINE_CPP) $(PIPELINE_HPP)
	g++ -c $(PIPELINE_CPP) -o $(PIPELINE_O)

# Creating directories if they do not exist.
$(DIRS):
	mkdir -p $(DIRS)

# Cleaning all the object and executable files, as well as object and
# executable subdirectories.
clean:
	rm -f $(EXES) $(OBJS)
	rm -rf $(OBJ_D)
