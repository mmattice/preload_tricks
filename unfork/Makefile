#
#

CC = gcc
CFLAGS = -shared -fPIC -Wall
LDFLAGS = -ldl

.PHONY: all
all: unfork.so

debug: CFLAGS += -DDEBUG -g
debug: all

%.so: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $<

clean:
	rm -vf *.so *.o
