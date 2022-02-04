#
#

CC = gcc
CFLAGS = -shared -fPIC -Wall
LDFLAGS = -ldl

.PHONY: all
all: logforce.so

debug: CFLAGS += -DDEBUG -g
debug: all

test: debug check-logs.o
	@echo 'Test WITH preload'
	LD_PRELOAD=./logforce.so ./check-logs.o
	@echo 'Test WITHOUT preload'
	@if ./check-logs.o; then echo "  *** Test is unreliable: we're actually on ext4"; fi

%.so: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $<

clean:
	rm -vf logforce.so checklogs.o
