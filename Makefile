CC = gcc

CFLAGS = -g -O2
LDFLAGS = 

# Version checking logic/message gratefully borrowed from the Linux kernel's
# top-level Makefile:
#
#   <https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/plain/Makefile>
#
ifeq ($(filter undefine,$(.FEATURES)),)
  $(error GNU Make >= 3.82 is required. Your Make version is $(MAKE_VERSION))
endif

ifeq ("$(origin D)", "command line")
  ifeq ("$(D)", "1")
    CFLAGS += -DDEBUG_BUILD=1
  endif
endif

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
