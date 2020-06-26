CC = g++

LDLIBS = -lglut -lGL -lGLU -lXxf86vm -std=c++11 -lm -lGLEW

PROG = puzzle

end:
	$(CC) main.cpp $(LDLIBS) -o $(PROG)


