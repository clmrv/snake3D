LIBS=-lglfw -lGLEW

ifeq ($(shell uname -s), Darwin)
LIBS += -framework OpenGL
else
LIBS += -lGL
endif

all:
	g++ -std=c++11 -o snake shader/*.cpp lodepng/*.cpp *.cpp $(LIBS)