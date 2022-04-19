#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 3
#
#  make                     makes FindComponents
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#------------------------------------------------------------------------------

targets = GraphClient FindComponents GraphTest
objs = Graph.o List.o

CC = gcc
CFLAGS = -std=c17 -Wall

COMPILE = $(CC) $(CFLAGS) -c -g
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

FindComponents: FindComponents.o $(objs)
	$(LINK) $@ $^

GraphClient: GraphClient.o $(objs)
	$(LINK) $@ $^

GraphTest: GraphTest.o $(objs)
	$(LINK) $@ $^

%.o: %.c
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt