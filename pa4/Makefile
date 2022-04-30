#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes Sparse
#  make GraphClient         makes MatrixClient
#  make GraphTest           makes MatrixTest
#  make clean               removes binaries and executables
#------------------------------------------------------------------------------
targets = ListClient MatrixTest MatrixClient Sparse
objs = List.o Matrix.o

CC = gcc
CFLAGS = -std=c17 -Wall

COMPILE = $(CC) $(CFLAGS) -c -g
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

Sparse: Sparse.o $(objs)
	$(LINK) $@ $^

MatrixTest: MatrixTest.o $(objs)
	$(LINK) $@ $^

MatrixClient: MatrixClient.o $(objs)
	$(LINK) $@ $^

ListClient: ListClient.o $(objs)
	$(LINK) $@ $^

all: $(targets)

%.o: %.c
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt