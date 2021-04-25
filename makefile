# Using this tutorial (made a bit more verbose for readibility):
# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/

# Use normal gcc for compiling
CCOMPILER = gcc

# Use include flag, enable debugging and enable all warnings as errors
CFLAGS = -I. -g -Wall -Werror

all: my-cat my-grep my-zip my-unzip

my-cat: my-cat.c
	$(CCOMPILER) -o $@ $^ $(CFLAGS)

my-grep: my-grep.c
	$(CCOMPILER) -o $@ $^ $(CFLAGS)

my-zip: my-zip.c
	$(CCOMPILER) -o $@ $^ $(CFLAGS)

my-unzip: my-unzip.c
	$(CCOMPILER) -o $@ $^ $(CFLAGS)

clean:
	rm -f my-cat
	rm -f my-grep
	rm -f my-zip
	rm -f my-unzip