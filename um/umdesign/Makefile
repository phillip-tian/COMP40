#
# Makefile for the UM (testing purpose)
# 
CC = gcc

IFLAGS  = -I/comp/40/include -I/usr/sup/cii40/include/cii
CFLAGS  = -g -std=gnu99 -Wall -Wextra -Werror -pedantic $(IFLAGS)
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64
LDLIBS  = -l40locality -lcii40 -lm
INCLUDES = $(shell echo *.h)

EXECS   = segment_test um

all: $(EXECS)

segment_test: segment_test.o 
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: um.o load.o bitpack.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(EXECS)  *.o