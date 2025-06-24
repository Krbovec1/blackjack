CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = blackjack
SRCDIR = src
OBJECTS = $(SRCDIR)/main.o $(SRCDIR)/gamelogic.o $(SRCDIR)/util.o $(SRCDIR)/colors.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(SRCDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/blackjack.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(SRCDIR)/main.o

$(SRCDIR)/gamelogic.o: $(SRCDIR)/gamelogic.c $(SRCDIR)/blackjack.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/gamelogic.c -o $(SRCDIR)/gamelogic.o

$(SRCDIR)/util.o: $(SRCDIR)/util.c $(SRCDIR)/blackjack.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/util.c -o $(SRCDIR)/util.o

$(SRCDIR)/colors.o: $(SRCDIR)/colors.c $(SRCDIR)/colors.h
	$(CC) $(CFLAGS) -c $(SRCDIR)/colors.c -o $(SRCDIR)/colors.o

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean rebuild run