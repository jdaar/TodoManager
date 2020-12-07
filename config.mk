# C compiler
CC=gcc

# Paths
LOCAL_DIR = /usr/local
JSON_PATH = /home/${USER}/.local/share/tm
INSTALL_DIR = /home/${USER}/.local

# Compiler flags
CFLAGS = -std=c99 -I$(LOCAL_DIR)/include/lib -ljson-c
LDFLAGS = -L$(LOCAL_DIR)/libjson-c

