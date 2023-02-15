CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -pedantic
LDLIBS = -luser32 -lgdi32
SRCDIR = src
OBJDIR = obj
BINDIR = bin

ihateyou: $(OBJDIR)/main.o
	$(CC) $(CFLAGS) $< -o $(BINDIR)/$@ $(LDLIBS)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(BINDIR)/ihateyou
