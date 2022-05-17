targets = ListClient Arithmetic ListTest BigIntegerTest *Client
objs = List.o BigInteger.o

CC = g++
CFLAGS = -std=c++17 -Wall 

COMPILE = $(CC) $(CFLAGS) -g -c  
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

BigIntegerClient: BigIntegerClient.o $(objs)
	$(LINK) $@ $^

BigIntegerTest: BigIntegerTest.o $(objs)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt