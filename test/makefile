SOURCE	= circular-buffer.c.o
SOURCE 	+= circular-buffer-test.cpp.o

INCLUDE =  -I /Users/Dakota/Source/external/googletest/googletest/include -I ../
LIBS = gtest_main.a

OUTPUT = test

CC	= gcc
CPP	= g++
LD	= ld

all: $(SOURCE) $(LIBS)
	$(CPP) $^ -o $(OUTPUT)

circular-buffer.c.o: ../circular-buffer.c ../circular-buffer.h
	$(CC) $(INCLUDE) -c -o $@ $<

circular-buffer-test.cpp.o: circular-buffer-test.cpp ../circular-buffer.h
	$(CPP) $(INCLUDE) -c -o $@ $<

.PHONY: clean
clean:
	rm *.o $(OUTPUT)
