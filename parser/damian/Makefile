####################################
# Theory of Computing - CS 421
####################################
CC = g++
CFLAGS = -g -Wall -std=c++11
LDFLAGS = -L.
PROG = main
SRCS = main.cpp scanner.cpp mparser.cpp
OBJ = $(SRCS:.cpp=.o)

all : $(PROG) depend

$(PROG): $(OBJ)
	$(CC) -o $(PROG) $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CC) $(CFLAGS) -MM $^ > ./.depend;

#include .depend

# clean up
clean:
	/bin/rm -f *.o $(PROG) .depend
