CC = gcc
CC_WIN = x86_64-w64-mingw32-gcc
CFLAGS = -Wall -Wextra -std=c99
CFLAGS_WIN = -Wall -Wextra -std=c99 -static-libgcc -static-libstdc++ -Wl,--nxcompat -Wl,--dynamicbase
TARGET = blackjack
TARGET_WIN = blackjack_game.exe
SRCDIR = src
BUILDDIR = build
BUILDDIR_WIN = build/win
OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/gamelogic.o $(BUILDDIR)/util.o
OBJECTS_WIN = $(BUILDDIR_WIN)/main.o $(BUILDDIR_WIN)/gamelogic.o $(BUILDDIR_WIN)/util.o

all: $(TARGET)

# Linux
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/blackjack.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/main.c -o $(BUILDDIR)/main.o

$(BUILDDIR)/gamelogic.o: $(SRCDIR)/gamelogic.c $(SRCDIR)/blackjack.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/gamelogic.c -o $(BUILDDIR)/gamelogic.o

$(BUILDDIR)/util.o: $(SRCDIR)/util.c $(SRCDIR)/blackjack.h | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $(SRCDIR)/util.c -o $(BUILDDIR)/util.o

# Windows
win: $(TARGET_WIN)

$(TARGET_WIN): $(OBJECTS_WIN)
	$(CC_WIN) $(OBJECTS_WIN) -o $(TARGET_WIN) -lkernel32 -luser32
	$(CC_WIN)-strip $(TARGET_WIN) 2>/dev/null || strip $(TARGET_WIN) 2>/dev/null || true

$(BUILDDIR_WIN)/main.o: $(SRCDIR)/main.c $(SRCDIR)/blackjack.h | $(BUILDDIR_WIN)
	$(CC_WIN) $(CFLAGS_WIN) -c $(SRCDIR)/main.c -o $(BUILDDIR_WIN)/main.o

$(BUILDDIR_WIN)/gamelogic.o: $(SRCDIR)/gamelogic.c $(SRCDIR)/blackjack.h | $(BUILDDIR_WIN)
	$(CC_WIN) $(CFLAGS_WIN) -c $(SRCDIR)/gamelogic.c -o $(BUILDDIR_WIN)/gamelogic.o

$(BUILDDIR_WIN)/util.o: $(SRCDIR)/util.c $(SRCDIR)/blackjack.h | $(BUILDDIR_WIN)
	$(CC_WIN) $(CFLAGS_WIN) -c $(SRCDIR)/util.c -o $(BUILDDIR_WIN)/util.o

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

$(BUILDDIR_WIN):
	mkdir -p $(BUILDDIR_WIN)

both: $(TARGET) $(TARGET_WIN)

clean:
	rm -rf $(BUILDDIR) $(TARGET) $(TARGET_WIN)

re: clean all

rewin: clean win

run: $(TARGET)
	./$(TARGET)

runwin: $(TARGET_WIN)
	wine $(TARGET_WIN)

.PHONY: all win both clean re rewin run runwin