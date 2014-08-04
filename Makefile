CFLAGS := -std=c99 \
	-Wall -Wextra -pedantic \
	-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
	${CFLAGS}

LDFLAGS = -lm

perfect: lookupa.o recycle.o perfhex.o perfect.o
testperf: testperf.o recycle.o phash.o lookupa.o

clean:
	${RM} perfect perftest *.o

.PHONY: all clean install uninstall
