#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS := -Wall -Wextra -Wpedantic -Werror -pedantic-errors -c -O3 -g
AR := ar
ARFLAGS := -rcs

all: libbase.a base.h
.PHONY: all

libbase.a: emperor-lists.o ./versioned-pointers.o ./base-io.o ./generics.o
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

base.h:;
%.h: %.c;

clean:
	$(RM) *.o *.a *.tar *.gz
.PHONY: clean
