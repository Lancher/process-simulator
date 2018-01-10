#compiler
CC = gcc
#cflags
CFLAGS = -c
#source location
SRC = src
#object
OBJS = $(SRC)/ArchiProject.o $(SRC)/I_Type.o $(SRC)/R_Type.o $(SRC)/J_Type.o $(SRC)/Other.o 
	
#BODY ->
all : single_cycle clean

single_cycle : $(OBJS)
	$(CC) $(OBJS) -o $@

clean : 
	rm -f $(OBJS) 
