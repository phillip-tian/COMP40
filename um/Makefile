#
# Makefile for the UM 
# 
CC = gcc

IFLAGS  = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS  = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS  = -lcii40-O2 -l40locality -lm -lcii40 -lrt
INCLUDES = $(shell echo *.h)

EXECS   = um segment_test

all: $(EXECS)

segment_test: segment_test.o memory.o
	$(CC) -O2 $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: um.o load.o bitpack.o memory.o instruction.o vm.o 
	$(CC) -O2 $(LDFLAGS) $^ -o $@ $(LDLIBS)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) -O2 $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECS)  *.o