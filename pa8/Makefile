#*************************************************************************************
# make/ make WordFrequency -> creates the WordFrequency executable
# make Order -> creates the Order executable
# make DictionaryClient -> creates the executable for the Dictionary ADT
# make DictionaryTest -> creates the test harness executable for the Dict ADT
#*************************************************************************************
targets = DictionaryClient DictionaryTest Order WordFrequency
objs = Dictionary.o

CC = g++
CFLAGS = -std=c++17 -Wall

COMPILE = $(CC) $(CFLAGS) -g -c
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

WordFrequency: WordFrequency.o $(objs)
	$(LINK) $@ $^

Order: Order.o $(objs)
	$(LINK) $@ $^

DictionaryClient: DictionaryClient.o $(objs)
	$(LINK) $@ $^

DictionaryTest: DictionaryTest.o $(objs)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< $(DEPFLAGS)

clean:
	rm -rf $(targets) *.o *.d *.txt