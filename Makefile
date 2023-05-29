CC=gcc
CFLAGS=-Wall -Wextra -O0 -g -Iinclude -std=c11

LD=gcc
LDFLAGS=

CFILES=$(shell find src -name '*.c')
OBJS=${CFILES:.c=.o}

TARGET=vcbc

.PHONY: all clean

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	rm -rf $(TARGET) $(OBJS)