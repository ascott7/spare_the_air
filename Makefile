CC=clang
CFLAGS= -g -Wall -Wextra -pedantic -O2 -std=c99

TARGETS= spare_the_air

export MAKEFLAGS="-j 4"

all: $(TARGETS)

temp_control: spare_the_air.c pi_helpers.h
	$(CC) $(CFLAGS) -o $@ $< -lm

clean:
	rm -f $(TARGETS) *.o

