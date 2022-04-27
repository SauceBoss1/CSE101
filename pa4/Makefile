targets = ListClient MatrixTest
objs = List.o Matrix.o

CC = gcc
CFLAGS = -std=c17 -Wall

COMPILE = $(CC) $(CFLAGS) -c -g
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

MatrixTest: MatrixTest.o $(objs)
	$(LINK) $@ $^

ListClient: ListClient.o $(objs)
	$(LINK) $@ $^

%.o: %.c
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt