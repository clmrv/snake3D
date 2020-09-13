LIBS=-framework OpenGL -lglfw -lGLEW

all:
	g++ -std=c++11 -o snake shader/*.cpp lodepng/*.cpp *.cpp $(LIBS)
