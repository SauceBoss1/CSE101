#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

targets = GraphClient
objs = Graph.o List.o GraphClient.o

CC = gcc
CFLAGS = -std=c17 -Wall

COMPILE = $(CC) $(CFLAGS) -c -g
LINK = $(CC) $(CFLAGS) -o

deps := $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

GraphClient: $(objs)
	$(LINK) $@ $^

%.o: %.c
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o $(deps)