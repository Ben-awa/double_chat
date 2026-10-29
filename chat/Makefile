cat > chat/Makefile << 'EOF'
CC      ?= gcc
CFLAGS  ?= -Wall -Wextra -Iinclude
LDFLAGS ?=

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

COMMON = $(SRC_DIR)/chat.c
SENDER = $(SRC_DIR)/sender.c
RECEIVER = $(SRC_DIR)/receiver.c

SENDER_OBJ = $(BUILD_DIR)/chat.o $(BUILD_DIR)/sender.o
RECEIVER_OBJ = $(BUILD_DIR)/chat.o $(BUILD_DIR)/receiver.o

SENDER_BIN = $(BIN_DIR)/chat_sender
RECEIVER_BIN = $(BIN_DIR)/chat_receiver

all: directories $(SENDER_BIN) $(RECEIVER_BIN)

directories:
	@mkdir -p $(BUILD_DIR) $(BIN_DIR)

$(BUILD_DIR)/chat.o: $(SRC_DIR)/chat.c include/chat.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/sender.o: $(SRC_DIR)/sender.c include/chat.h
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/receiver.o: $(SRC_DIR)/receiver.c include/chat.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SENDER_BIN): $(SENDER_OBJ)
	$(CC) $(SENDER_OBJ) -o $@ $(LDFLAGS)

$(RECEIVER_BIN): $(RECEIVER_OBJ)
	$(CC) $(RECEIVER_OBJ) -o $@ $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all clean directories
EOF
