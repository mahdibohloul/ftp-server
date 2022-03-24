CC = g++
BUILD_DIR = out
SRC_DIR = src
HEADERS = $(shell find $(SRC_DIR) -name '*.hpp')
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
CFLAGS = -std=c++20 -pthread -Wall -Werror -I$(HEADERS)

TARGET = server.out


clean:
	rm -f $(BUILD_DIR)/$(TARGET)


