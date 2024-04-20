CC := clang++
CFLAGS := -Wall
CFLAGS += -std=c++11
CFLAGS += -O2
LFLAGS := 

ODIR := .OBJ

TESTS_JUMP_TESTS_SOURCE_DEPS := tests/jump_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
TESTS_GLOBAL_TESTS_SOURCE_DEPS := tests/global_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
TESTS_CALL_TESTS_SOURCE_DEPS := tests/call_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
MAIN_SOURCE_DEPS := main.cpp cli.h virtual_machine.h virtual_machine.cpp common.h format_buffer.h format_buffer.cpp entire_file.h
TESTS_STACK_TESTS_SOURCE_DEPS := tests/stack_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
TESTS_MATH_TESTS_SOURCE_DEPS := tests/math_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
FORMAT_BUFFER_SOURCE_DEPS := format_buffer.cpp common.h format_buffer.h
TESTS_COMPARISON_TESTS_SOURCE_DEPS := tests/comparison_tests.cpp tests/unit_test.h common.h virtual_machine.h virtual_machine.cpp format_buffer.h format_buffer.cpp
VIRTUAL_MACHINE_SOURCE_DEPS := virtual_machine.cpp common.h virtual_machine.h format_buffer.h format_buffer.cpp

all: binaries

$(ODIR):
	@mkdir $(ODIR)

binaries: vm 

MAIN_OBJECT_DEPS := $(ODIR)/main.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

vm: $(ODIR) $(MAIN_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(MAIN_OBJECT_DEPS) -o vm $(LFLAGS)

tests: tests_math_tests tests_stack_tests tests_call_tests tests_comparison_tests tests_jump_tests tests_global_tests 

TESTS_MATH_TESTS_OBJECT_DEPS := $(ODIR)/tests_math_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_math_tests: $(ODIR) $(TESTS_MATH_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_MATH_TESTS_OBJECT_DEPS) -o tests/math_tests

TESTS_STACK_TESTS_OBJECT_DEPS := $(ODIR)/tests_stack_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_stack_tests: $(ODIR) $(TESTS_STACK_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_STACK_TESTS_OBJECT_DEPS) -o tests/stack_tests

TESTS_CALL_TESTS_OBJECT_DEPS := $(ODIR)/tests_call_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_call_tests: $(ODIR) $(TESTS_CALL_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_CALL_TESTS_OBJECT_DEPS) -o tests/call_tests

TESTS_COMPARISON_TESTS_OBJECT_DEPS := $(ODIR)/tests_comparison_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_comparison_tests: $(ODIR) $(TESTS_COMPARISON_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_COMPARISON_TESTS_OBJECT_DEPS) -o tests/comparison_tests

TESTS_JUMP_TESTS_OBJECT_DEPS := $(ODIR)/tests_jump_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_jump_tests: $(ODIR) $(TESTS_JUMP_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_JUMP_TESTS_OBJECT_DEPS) -o tests/jump_tests

TESTS_GLOBAL_TESTS_OBJECT_DEPS := $(ODIR)/tests_global_tests.o $(ODIR)/virtual_machine.o $(ODIR)/format_buffer.o

tests_global_tests: $(ODIR) $(TESTS_GLOBAL_TESTS_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(TESTS_GLOBAL_TESTS_OBJECT_DEPS) -o tests/global_tests

$(ODIR)/tests_jump_tests.o: $(ODIR) $(TESTS_JUMP_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/jump_tests.cpp -o $(ODIR)/tests_jump_tests.o

$(ODIR)/tests_global_tests.o: $(ODIR) $(TESTS_GLOBAL_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/global_tests.cpp -o $(ODIR)/tests_global_tests.o

$(ODIR)/tests_call_tests.o: $(ODIR) $(TESTS_CALL_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/call_tests.cpp -o $(ODIR)/tests_call_tests.o

$(ODIR)/main.o: $(ODIR) $(MAIN_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) main.cpp -o $(ODIR)/main.o

$(ODIR)/tests_stack_tests.o: $(ODIR) $(TESTS_STACK_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/stack_tests.cpp -o $(ODIR)/tests_stack_tests.o

$(ODIR)/tests_math_tests.o: $(ODIR) $(TESTS_MATH_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/math_tests.cpp -o $(ODIR)/tests_math_tests.o

$(ODIR)/format_buffer.o: $(ODIR) $(FORMAT_BUFFER_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) format_buffer.cpp -o $(ODIR)/format_buffer.o

$(ODIR)/tests_comparison_tests.o: $(ODIR) $(TESTS_COMPARISON_TESTS_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) tests/comparison_tests.cpp -o $(ODIR)/tests_comparison_tests.o

$(ODIR)/virtual_machine.o: $(ODIR) $(VIRTUAL_MACHINE_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) virtual_machine.cpp -o $(ODIR)/virtual_machine.o

.PHONY: clean
clean:
	rm -rf .OBJ vm tests/math_tests tests/stack_tests tests/call_tests tests/comparison_tests tests/jump_tests tests/global_tests 
