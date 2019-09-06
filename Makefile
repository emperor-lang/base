#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS := -Wall -Wextra -Wpedantic -Werror -pedantic-errors -c -O3 -g
AR := ar
ARFLAGS := -rcs

all: libbase.a base.h.gch
.PHONY: all

libbase.a: $(shell find . -name '*.c' | grep -v 'test.c' | sed 's/.c$$/.o/')
	$(AR) $(ARFLAGS) $@ $^

base.h.gch: ./base.h
	$(CC) $(CFLAGS) $< -o $@

./base.h: $(shell find . -name '*.h' | grep -v 'base.h')

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

%.h: %.c;

clean:
	$(RM) **/*.o *.a *.tar *.gz *.gch
.PHONY: clean
