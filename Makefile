#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS := -Wall -Wextra -Wpedantic -Werror -pedantic-errors -c -O3 -g
AR := ar
ARFLAGS := -rUucs

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

lint: $(shell find . -name '*.[ch]')
	splint $^
.PHONY: lint

doc: ./doc/html/index.html
.PHONY: doc

./doc/html/index.html: $(shell find . -name '*.[ch]') ./doxygen.conf
	doxygen ./doxygen/doxygen.conf

%.conf:;

./doc/:
	mkdir $@

format: $(shell find . -name '*.[ch]' | grep -v banned/)
	clang-format -style=file -i $^

clean:
	$(RM) **/*.o *.a *.tar *.gz *.gch
	$(RM) -r ./doc/
.PHONY: clean
