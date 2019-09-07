#!/usr/bin/make

.DEFAULT_GOAL := all

CC := gcc-8
CFLAGS = $(shell emperor-setup -cb)
AR := ar
ARFLAGS := -rUucs
LINTER := splint
LINTER_FLAGS = -D__linux +posixstrictlib -stats -showsummary -linelen $(shell stty size | grep -o '[0-9]*$$') -standard -mustfreefresh

ALL_SOURCE_FILES = $(shell find . -name '*.[ch]')
BASE_SOURCE_FILES = $(shell find . -name '*.[ch]' | grep -v banned/ | grep -v test/)

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

lint: $(BASE_SOURCE_FILES)
	$(LINTER) $(LINTER_FLAGS) $^
.PHONY: lint

doc: ./doc/html/index.html
.PHONY: doc

./doc/html/index.html: $(ALL_SOURCE_FILES) ./doxygen.conf
	doxygen ./doxygen/doxygen.conf

%.conf:;

./doc/:
	mkdir $@

format: $(BASE_SOURCE_FILES)
	clang-format -style=file -i $^

clean:
	$(RM) **/*.o *.a *.tar *.gz *.gch
	$(RM) -r ./doc/
.PHONY: clean
