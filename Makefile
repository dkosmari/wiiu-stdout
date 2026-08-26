TARGETS := \
	test-iostream.rpx \
	test-stdio.rpx


ifeq ($(strip $(DEVKITPRO)),)
$(error Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitPro)
endif

V ?= 1
include $(DEVKITPRO)/wut/share/wut_rules


COMMON_FLAGS := -mcpu=750 -meabi -mhard-float \
	-Wall -Wextra -Werror \
	-Os -ffunction-sections -fdata-sections

CPPFLAGS := \
	-DESPRESSO \
	-D__WIIU__ \
	-D__WUT__ \
	-I$(WUT_ROOT)/include

CFLAGS := $(COMMON_FLAGS) -Wall -Wextra -Werror

CXXFLAGS := $(COMMON_FLAGS) -std=c++23 -Wall -Wextra -Werror

LDFLAGS := $(RPXSPECS) -L$(WUT_ROOT)/lib

LIBS := -lwut


.PHONY: all clean \
	company \
	run-test-iostream \
	run-test-stdio


all: $(TARGETS)


clean:
	$(RM) $(TARGETS)
	$(RM) *.elf *.o tests/*.o


test-iostream.elf: 	tests/test-iostream.o \
			wiiu-stdout.o
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS) $(LDFLAGS)


test-stdio.elf:	tests/test-stdio.o \
		wiiu-stdout.o
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS) $(LDFLAGS)


%.o: %.cpp
	$(CXX) -c $< $(CPPFLAGS) $(CXXFLAGS) -o $@

%.o: %.c
	$(CC) -c $< $(CPPFLAGS) $(CFLAGS) -o $@



run-test-iostream: test-iostream.rpx
	WIILOAD=tcp:wiiu wiiload $<


run-test-stdio: test-stdio.rpx
	WIILOAD=tcp:wiiu wiiload $<


company: compile_flags.txt

compile_flags.txt: Makefile
	printf "%s" "$(CPPFLAGS)" | xargs -n1 | sort -u > compile_flags.txt
	$(CPP) -xc++ /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,-I,p' >> compile_flags.txt
