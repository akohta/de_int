CC  =gcc
LIB =-lm
FLAG=-O3 -Wall
OBJS=example.o de_int.o
OUT =example.out
OBJ2=example2.o de_int.o
OUT2=example2.out

all : $(OUT) $(OUT2)

$(OUT) : $(OBJS)
	$(CC) $(FLAG) $(OBJS) -o $(OUT) $(LIB)

$(OUT2) : $(OBJ2)
	$(CC) $(FLAG) $(OBJ2) -o $(OUT2) $(LIB)

.c.o :
	$(CC) $(FLAG) -c $<

clean :
	@rm -f $(OBJS) $(OBJ2) $(OUT) $(OUT2)

$(OBJS) $(OBJ2) : de_int.h
