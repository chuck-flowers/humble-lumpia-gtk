PREFIX ?= /usr/local
LIBS=gtk4

# Compilation Options
CC=gcc
CFLAGS=-g -Wall -c $(shell pkg-config --cflags $(LIBS))
LFLAGS=$(shell pkg-config --libs $(LIBS))

# Source files
SRC_DIR=src
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)

# Object files
OBJ_DIR=obj
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

# UI files
UI_DIR=ui
UI_FILES=$(wildcard $(UI_DIR)/*.ui)

# Desktop Files
APPS_DIR=applications
DESKTOP_FILES=$(wildcard $(APPS_DIR)/*.desktop)

# Binary files
BIN_DIR=bin
BIN_NAME=humble-lumpia-gtk
BIN_FILE=$(BIN_DIR)/$(BIN_NAME)

# Creates all artifacts
.PHONY: all
all: $(BIN_FILE)

.PHONY: install
install: $(BIN_FILE)
	install -Dm 555 $(BIN_FILE) $(PREFIX)/bin/$(BIN_NAME)
	install -Dm 444 -t $(PREFIX)/share/humble-lumpia-gtk/ui $(UI_FILES)
	install -Dm 444 -t $(PREFIX)/share/applications $(DESKTOP_FILES)
	install -Dm 444 -t $(PREFIX)/share/icons/hicolor/48x48/apps icons/humble-lumpia.png

.PHONY: uninstall
uninstall:
	-rm -f $(PREFIX)/bin/$(BIN_NAME)
	-rm -rf $(PREFIX)/share/humble-lumpia-gtk/ui
	-rm -f $(patsubst %, $(PREFIX)/share/%, $(DESKTOP_FILES))
	-rm -f $(PREFIX)/share/icons/hicolor/48x48/apps/humble-lumpia.png

.PHONY: debug
debug: $(BIN_FILE)
	$(BIN_FILE)

.PHONY: clean
clean:
	-rm -r $(BIN_DIR)
	-rm -r $(OBJ_DIR)

# Links all build output together
$(BIN_FILE): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(LFLAGS) -o $@ $^

# Compiles object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ $<

