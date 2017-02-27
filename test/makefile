
SOURCE	= circular-buffer.c.o
SOURCE 	+= circular-buffer-test.cpp.o

INCLUDE =  -I /Users/Dakota/Source/external/googletest/googletest/include
LIBS = gtest_main.a

CC	= gcc
CPP	= g++
LD	= ld

%.c.o: %.c circular-buffer.h
	$(CC) $(INCLUDE) -c -o $@ $<

%.cpp.o: %.cpp circular-buffer.h
	$(CPP) $(INCLUDE) -c -o $@ $<

all: $(SOURCE) $(LIBS)
	$(CPP) $^ -o output
	
.PHONY: clean
clean:
	rm *.o