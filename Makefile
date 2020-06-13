LIBS=-framework OpenGL -lglfw -lGLEW

all:
	g++ -std=c++11 -o snake myCube/shaderprogram.cpp *.cpp $(LIBS)