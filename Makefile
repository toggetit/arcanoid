CC = g++
SRCDIR = src
OBJDIR = bin

all : arcanoid

arcanoid: gamecore.o main.o
	$(CC) $(OBJDIR)/gamecore.o $(OBJDIR)/main.o -lSDL2 -o arcanoid

main.o: $(SRCDIR)/main.cpp
	$(CC) -c $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o

gamecore.o: $(SRCDIR)/gamecore.cpp
	$(CC) -c $(SRCDIR)/gamecore.cpp -o $(OBJDIR)/gamecore.o

clean:
	rm $(OBJDIR)/*.o

