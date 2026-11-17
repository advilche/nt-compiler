CC = gcc
CFLAGS = -Wall -Wextra -g
DEPFLAGS = -MMD -MP

TARGET = parser

SRCS = parser.c parserhelper.c lex.c lexhelper.c
HEADERS = parserhelper.h lexhelper.h
OBJS = $(SRCS:.c=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

format:
	clang-format -i $(SRCS) $(HEADERS)

.PHONY: all clean format