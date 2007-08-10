CC=g++
LD=g++

CFLAGS=-g -Wall `fltk2-config --cflags` -O0
CXXFLAGS=-g -Wall `fltk2-config --cxxflags` -O0
LDFLAGS=`fltk2-config --ldstaticflags --use-images`
LDLIBS=
LIBS=

SRC=test1.cpp TableBox.cpp
OBJ=$(SRC:.cpp=.o)
EXE=test1

all: $(SRC) $(EXE)
	
$(EXE): $(OBJ)
	$(LD) $(OBJ) -o $(EXE) $(LDFLAGS) $(LIBS) $(LDLIBS)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXE)