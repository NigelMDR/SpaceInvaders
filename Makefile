CXXFLAGS=-ggdb3
LDLIBS=-lX11 -lstdc++ -lm
MACF = -I/usr/X11R6/include -L/usr/X11R6/lib

main: main.o drawCharacters.o gfx.o

clean: 
	rm -f main *.o

