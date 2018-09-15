# Macros para compilacao
CC = g++
CFLAGS = -std=c++11 -lncurses -lpthread -lportaudio
DIR = src
TARGET = snake\ single\ player
SRCS := $(shell find $(DIR) -name '*.cpp')
OBJS = $(SRCS:.c=.o)

.PHONY: depend clean

all:$(TARGET)

$(TARGET):$(OBJS)
	$(CC) -o$(TARGET) $(OBJS) $(CFLAGS)

%.o:%.cpp
	$(CC) $(SRCS) $(CFLAGS) -c $< -o $@

run:all
	./$(TARGET)

clean:
	$(RM) ./$(TARGET)
	$(RM) $(DIR)/*.o