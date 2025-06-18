CC = g++

CFLAGS = -c

OBJECTS = integer1.o float2.o calculator.o

LIB = integer1.o float2.o

all: prog

prog : $(OBJECTS)
	
	$(CC) $(OBJECTS) -o my_inf_arith
%.o :%.cpp
	$(CC) $(CFLAGS) $< -o $@
libmy_inf_arith: library

library:$(LIB)
	ar rcs libmy_inf_arith.a $(LIB)

%.o:%.cpp
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f *.o my_inf_arith libmy_inf_arith.a


