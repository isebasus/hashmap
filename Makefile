EXECA = hashtest
UTIL = ./hashmap/util
SRC = ./hashmap

SOURCEA = $(UTIL)/list.o $(UTIL)/node.o $(SRC)/hashmap.o hashtest.o

OBJECTSA = $(SOURCEA:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LFLAGS = -lm

.PHONY: all clean

all: $(EXECA)

$(EXECA): $(OBJECTSA)
	$(CC) $(CFLAGS) $(SOURCEA) -o $(EXECA)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(EXECA) $(OBJECTSA) 

scan-build: clean
	scan-build make 