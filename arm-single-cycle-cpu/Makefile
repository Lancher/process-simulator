#compiler
CC = gcc
#cflags
CFLAGS = -c
#source location
SRC = src
#object
OBJS = $(SRC)/single_cycle.o $(SRC)/ALU_ins.o $(SRC)/Branch_ins.o $(SRC)/DATA_ins.o $(SRC)/Other.o 
	
#BODY ->
all : single_cycle

single_cycle : $(OBJS)
	$(CC) $(OBJS) -o $@

clean : 
	rm -f $(OBJS) single_cycle
