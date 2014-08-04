CFLAGS := -std=c99 \
	-Wall -Wextra -pedantic \
	-Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes \
	${CFLAGS}

LDFLAGS = -lm

perfect: lookupa.o recycle.o perfhex.o perfect.o

clean:
	${RM} perfect *.o

.PHONY: all clean install uninstall
