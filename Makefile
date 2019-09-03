#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS := -Wall -Wextra -Wpedantic -Werror -pedantic-errors -c -O3
AR := ar
ARFLAGS := -rcs

all: libbase.a emperor-lists.h
.PHONY: all

libbase.a: emperor-lists.o
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

%.h: %.c;

clean:
	$(RM) *.o *.a *.tar *.gz
.PHONY: clean
