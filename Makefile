#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS := -Wall -Wextra -Wpedantic -Werror -pedantic-errors -Wno-missing-braces -c -O3 -g
AR := ar
ARFLAGS := -rcs

all: libbase.a base.h
.PHONY: all

libbase.a: ./lists/base-lists.o ./references/base-references.o ./io/base-io.o ./generics/base-generics.o
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) $< -o $@

base.h:;
%.h: %.c;

clean:
	$(RM) **/*.o *.a *.tar *.gz
.PHONY: clean
