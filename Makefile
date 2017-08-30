BUILD_DIR ?= ./build
TARGET ?= hgen.out

CC ?= gcc

SRC_DIR ?= ./src
SRCS = $(shell find ./src -name *.c)

INC_DIR := $(shell find $(SRC_DIR) -type d) 
INCS := $(addprefix -I,$(INC_DIR)) 

FLAGS ?= -MP

all: builddir 
	$(CC) -o $(BUILD_DIR)/$(TARGET) $(INCS) $(SRCS)

.PHONY: clean builddir

clean: 
	rm -rf $(BUILD_DIR)

builddir: $(BUILD_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
