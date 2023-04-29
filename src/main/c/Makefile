SOURCES := ${wildcard *.c}
TARGETS := $(SOURCES:%.c=%)

all: $(TARGETS)

%: %.c
	gcc -o $@ $< -lm
	@# If target exists, run it.
ifeq ($(OS),Windows_NT)
	@# To do.
else
	[ -f ./$@ ] && (./$@ > ./$@.svg)
endif

clean:
	rm -rf *.o
