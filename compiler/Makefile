CC := clang++
CFLAGS := -Wall
CFLAGS += -std=c++11
CFLAGS += -O2
LFLAGS := 

ODIR := .OBJ

MAIN_SOURCE_DEPS := main.cpp cli.h common.h entire_file.h

all: binaries

$(ODIR):
	@mkdir $(ODIR)

binaries: bytecode-cc 

MAIN_OBJECT_DEPS := $(ODIR)/main.o

bytecode-cc: $(ODIR) $(MAIN_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(MAIN_OBJECT_DEPS) -o bytecode-cc $(LFLAGS)

$(ODIR)/main.o: $(ODIR) $(MAIN_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) main.cpp -o $(ODIR)/main.o

.PHONY: clean
clean:
	rm -rf .OBJ bytecode-cc 
