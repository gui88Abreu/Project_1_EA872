# Macros para compilacao
CC = g++
CFLAGS = -std=c++11 -lncurses -lpthread -lportaudio
ASSETS_ZIP = audio/assets/assets.zip
ASSETS_DIR = audio/assets
STAT_DIR = statistics
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

run:all extract
	./$(TARGET)

extract:
	unzip $(ASSETS_ZIP) -d $(ASSETS_DIR)/

clean:
	$(RM) ./$(TARGET)
	$(RM) $(DIR)/*.o
	$(RM) $(ASSETS_DIR)/*.dat
	$(RM) $(STAT_DIR)/*.est