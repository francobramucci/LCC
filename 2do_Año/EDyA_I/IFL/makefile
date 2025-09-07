CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c99 -g -lm -O2

SRCS = apply.c dlist.c flista.c lista.c main.c parser.c pila.c search.c thash.c token.c utils.c vector.c
OBJS = $(SRCS:.c=.o)

TARGET = ifl

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

main.o: main.c

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
