# Define the compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = lex.c lexhelper.c lexhelper.h

# Name of your final executable output
TARGET = lexer

# List all the object files that need to be linked together
OBJS = lex.o lexhelper.o

# The default target that runs when you just type 'make'
all: $(TARGET)

# Rule to link the object files into the final executable
# $@ matches the target (my_program)
# $^ matches all the dependencies (main.o helper.o)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile .c files into .o files
# $< matches the first dependency (the .c file)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

# Declare format as a phony target so it doesn't conflict with a file named 'format'
.PHONY: format

# The format rule
format:
	clang-format -i $(SRCS)


