# RaspPiOS
An OS for Raspberry Pi 2
C_SOURCE = \
			main.c \
			bstree.c
OBJ_FILE = \
			main.o \
			bstree.o
			
CC = gcc
FLAGS = -c -g -Wall
TARGET = myBst

all: $(TARGET)

$(TARGET): $(OBJ_FILE)
	$(CC) $(OBJ_FILE) -o $(TARGET)
	
%.o:%.c
	$(CC) $(FLAGS) $< -o $@
