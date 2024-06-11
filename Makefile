CC = gcc

CFLAGS = -g -O2
LDFLAGS = 

BIN_TARGETS = \
  ascii-calc

ALL_TARGETS += $(BIN_TARGETS)

.PHONY: all
all: $(ALL_TARGETS)

ascii-calc: src/ascii-calc.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY:
clean:
	-rm -f $(ALL_TARGETS)

#
# vim: ts=8 sw=8 noet fdm=marker :
