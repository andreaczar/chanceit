BUILDDIR=./build
BINDIR=./bin
SRCDIR=./src

chanceit:	player controller roll prob ui input game humanplayer aiplayer highscore socket protocol
	mkdir -p $(BINDIR)
	mkdir -p $(BUILDDIR)
	gcc -o $(BINDIR)/chanceit $(BUILDDIR)/roll.o $(BUILDDIR)/prob.o $(BUILDDIR)/player.o $(BUILDDIR)/ui.o $(BUILDDIR)/controller.o $(BUILDDIR)/input.o $(BUILDDIR)/game.o $(BUILDDIR)/humanplayer.o $(BUILDDIR)/aiplayer.o $(BUILDDIR)/highscore.o $(BUILDDIR)/socket.o $(BUILDDIR)/protocol.o

controller:	$(SRCDIR)/roll.h $(SRCDIR)/ui.h $(SRCDIR)/prob.h $(SRCDIR)/socket.h
	mkdir -p $(BUILDDIR)
	gcc -c $(SRCDIR)/controller.c -o $(BUILDDIR)/controller.o

roll:	$(SRCDIR)/roll.c $(SRCDIR)/roll.h
	gcc -c $(SRCDIR)/roll.c -o $(BUILDDIR)/roll.o

prob:	$(SRCDIR)/prob.c $(SRCDIR)/prob.h
	gcc -c $(SRCDIR)/prob.c -o $(BUILDDIR)/prob.o

ui:	$(SRCDIR)/ui.c $(SRCDIR)/ui.h $(SRCDIR)/input.h
	gcc -c $(SRCDIR)/ui.c -o $(BUILDDIR)/ui.o

input:	$(SRCDIR)/input.c $(SRCDIR)/input.h
	gcc -c $(SRCDIR)/input.c -o $(BUILDDIR)/input.o

player:	$(SRCDIR)/player.c $(SRCDIR)/player.h $(SRCDIR)/game.h $(SRCDIR)/humanplayer.h
	mkdir -p build
	gcc -c $(SRCDIR)/player.c -o $(BUILDDIR)/player.o

game:	$(SRCDIR)/game.h $(SRCDIR)/game.c
	gcc -c $(SRCDIR)/game.c -o $(BUILDDIR)/game.o

humanplayer: $(SRCDIR)/game.h $(SRCDIR)/humanplayer.c $(SRCDIR)/humanplayer.h
	gcc -c $(SRCDIR)/humanplayer.c -o $(BUILDDIR)/humanplayer.o

aiplayer: $(SRCDIR)/game.h $(SRCDIR)/humanplayer.c $(SRCDIR)/aiplayer.h
	gcc -c $(SRCDIR)/aiplayer.c -o $(BUILDDIR)/aiplayer.o

highscore: $(SRCDIR)/highscore.h $(SRCDIR)/ui.h
	gcc -c $(SRCDIR)/highscore.c -o $(BUILDDIR)/highscore.o

protocol: $(SRCDIR)/protocol.h
	gcc -c $(SRCDIR)/protocol.c -o $(BUILDDIR)/protocol.o

socket: $(SRCDIR)/socket.h $(SRCDIR)/protocol.h
	gcc -c $(SRCDIR)/socket.c -o $(BUILDDIR)/socket.o

clean:
	rm -rf $(BUILDDIR)/*
	rm -rf $(BINDIR)/*
