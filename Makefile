TARGETS := \
	test-cout.rpx \
	test-cerr.rpx \
	test-stdout.rpx \
	test-stderr.rpx


ifeq ($(strip $(DEVKITPRO)),)
$(error Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitPro)
endif

V ?= 1
include $(DEVKITPRO)/wut/share/wut_rules


COMMON_FLAGS := -mcpu=750 -meabi -mhard-float \
	-Wall -Wextra -Werror \
	-Os -ffunction-sections

CPPFLAGS := \
	-DESPRESSO \
	-D__WIIU__ \
	-D__WUT__ \
	-I$(WUT_ROOT)/include

CFLAGS := $(COMMON_FLAGS)

CXXFLAGS := $(COMMON_FLAGS) -std=c++23

LDFLAGS := $(RPXSPECS) -L$(WUT_ROOT)/lib

LIBS := -lwut


.PHONY: all clean \
	company \
	run-test-cout \
	run-test-cerr
	run-test-stdout \
	run-test-stderr


all: $(TARGETS)


clean:
	$(RM) $(TARGETS)
	$(RM) *.elf c/*.o cpp/*.o


test-cout.elf: tests/test-cout.o \
		cpp/stdout-wiiu.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(LDFLAGS)


test-cerr.elf: tests/test-cerr.o \
		cpp/stdout-wiiu.o \
		cpp/stderr-wiiu.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(LDFLAGS)


test-stdout.elf: tests/test-stdout.o c/stdout-wiiu.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)

test-stderr.elf: tests/test-stderr.o \
		c/stdout-wiiu.o \
		c/stderr-wiiu.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)


%.o: %.cpp
	$(CXX) -c $< $(CPPFLAGS) $(CXXFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@



run-test-cout: test-cout.rpx
	WIILOAD=tcp:wiiu wiiload $<

run-test-cerr: test-cerr.rpx
	WIILOAD=tcp:wiiu wiiload $<

run-test-stdout: test-stdout.rpx
	WIILOAD=tcp:wiiu wiiload $<

run-test-stderr: test-stderr.rpx
	WIILOAD=tcp:wiiu wiiload $<


company: compile_flags.txt

compile_flags.txt: Makefile
	printf "%s" "$(CPPFLAGS)" | xargs -n1 | sort -u > compile_flags.txt
	$(CPP) -xc++ /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,-I,p' >> compile_flags.txt
