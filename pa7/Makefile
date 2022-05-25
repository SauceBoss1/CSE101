#--------------------------------------------------------------
# make -> creates the Order executable
# make DictionaryTest -> creates Dictionary ADT test
# 								 harness
# make DictionaryClient -> creates Dictionary ADT client file
# make clean -> removes all executables
#--------------------------------------------------------------
targets = DictionaryClient DictionaryTest Order
objs = Dictionary.o

CC = g++
CFLAGS = -std=c++17 -Wall

COMPILE = $(CC) $(CFLAGS) -g -c
LINK = $(CC) $(CFLAGS) -o

deps = $(patsubst %.o,%.d, $(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

Order: Order.o $(objs)
	$(LINK) $@ $^

DictionaryClient: DictionaryClient.o $(objs)
	$(LINK) $@ $^

DictionaryTest: DictionaryTest.o $(objs)
	$(LINK) $@ $^

%.o: %.cpp
	$(COMPILE) $< $(DEPFLAGS)

all: $(targets)

clean:
	rm -rf $(targets) *.o *.d *.txt