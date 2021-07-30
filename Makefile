CC  =gcc
LIB =-lm
FLAG=-O3 -Wall
OBJS=example.o de_int.o
OUT =example.out

$(OUT) : $(OBJS)
	$(CC) $(LIB) $(OBJS) -o $(OUT)

.c.o :
	$(CC) $(FLAG) -c $<
	
clean :
	@rm $(OBJS) $(OUT)

$(OBJS) : de_int.h
