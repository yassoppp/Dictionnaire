# Compilateur
CC=gcc
# Options de compilation
CFLAGS=-std=c99 -Wall -Wextra -lm -g -pg

# DÃ©finition des rÃ©pertoires de travail
SRC_DIR=src
BIN_DIR=bin
INC_DIR=include
INC=-I$(INC_DIR)

# DÃ©finition des fichiers source ne contenant pas de main
AUX_SRC_FILES=""

# Identification des fichiers source dans le rÃ©pertoire SRC_DIR
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)
# Filtrage des fichiers source ne contenant pas de main
SRC_FILES := $(filter-out $(AUX_SRC_FILES), $(SRC_FILES))
# GÃ©nÃ©ration de la liste des exÃ©cutables
BIN_FILES=$(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRC_FILES))

# RÃ¨gle par dÃ©faut (make)
all: $(BIN_FILES)

# RÃ¨gle gÃ©nÃ©rique
$(BIN_DIR)/%: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $^ $(CFLAGS) $(INC) -o $@

$(BIN_DIR):
	mkdir $@

clean:
	rm -rf $(BIN_DIR)
	rm -f gmon.out