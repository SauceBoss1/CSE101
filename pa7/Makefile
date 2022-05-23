targets = DictionaryClient DictionaryTest Order
objs = Dictionary.o

CC = g++
CFLAGS = -std=c++17 -Wall

COMPILE = $(CC) $(CFLAGS) -g -c
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

DictionaryClient: DictionaryClient.o $(objs)
	$(LINK) $@ $^

DictionaryTest: DictionaryTest.o $(objs)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt