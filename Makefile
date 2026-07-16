.PHONY: all test debug clean
.SECONDARY:

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -fPIC -MMD -MP
CPPFLAGS = -Iinclude

AR = ar
ARFLAGS = rcs

LDFLAGS =
LDLIBS =

BUILDDIR = build/release

ifeq ($(filter debug test,$(MAKECMDGOALS)),)
CFLAGS += -O2
else
BUILDDIR = build/debug
CFLAGS += -Werror \
          -g \
          -O0 \
          -fsanitize=address,undefined \
          -fno-omit-frame-pointer
endif

OBJDIR = $(BUILDDIR)/obj
LIBDIR = $(BUILDDIR)/lib
BINDIR = $(BUILDDIR)/bin

TESTDIR = $(BINDIR)/tests
OBJTESTDIR = $(OBJDIR)/tests

OBJECTS = \
	$(OBJDIR)/lists/list.o \
	$(OBJDIR)/lists/dlist.o

DEPS = $(OBJECTS:.o=.d)

TESTS = \
	$(TESTDIR)/lists/test_list \
	$(TESTDIR)/lists/test_dlist

TESTOBJECTS := $(patsubst $(TESTDIR)/%, $(OBJTESTDIR)/%.o, $(TESTS))

TESTDEPS := $(TESTOBJECTS:.o=.d)

all: $(LIBDIR)/libdsa.so $(LIBDIR)/libdsa.a

$(LIBDIR)/libdsa.so: $(OBJECTS) | $(LIBDIR)
	$(LINK.c) -shared $^ $(LDLIBS) -o $@

$(LIBDIR)/libdsa.a: $(OBJECTS) | $(LIBDIR)
	$(AR) $(ARFLAGS) $@ $?

$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

$(OBJDIR):
	@mkdir -p $@

$(LIBDIR):
	@mkdir -p $@

$(BINDIR):
	@mkdir -p $@

$(TESTDIR):
	@mkdir -p $@

$(OBJTESTDIR):
	@mkdir -p $@

debug: all

test: $(TESTS)
	@for t in $(TESTS); do \
		$$t; \
	done

$(TESTDIR)/%: $(OBJTESTDIR)/%.o $(OBJECTS) | $(TESTDIR)
	@mkdir -p $(dir $@)
	$(LINK.c) $^ $(LDLIBS) -o $@

$(OBJTESTDIR)/%.o: tests/%.c | $(OBJTESTDIR)
	@mkdir -p $(dir $@)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

clean:
	rm -rf build

-include $(DEPS) $(TESTDEPS)
