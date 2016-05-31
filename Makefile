BUILDDIR=$(PWD)/build
BINDIR=$(PWD)/bin
SRCDIR=$(PWD)/src

chanceit:	controller.o roll.o prob.o ui.o input.o
	gcc -o $(BINDIR)/chanceit $(BUILDDIR)/roll.o $(BUILDDIR)/prob.o $(BUILDDIR)/ui.o $(BUILDDIR)/controller.o $(BUILDDIR)/input.o

controller.o:	$(SRCDIR)/roll.h $(SRCDIR)/ui.h $(SRCDIR)/prob.h
	gcc -c $(SRCDIR)/controller.c -o $(BUILDDIR)/controller.o

roll.o:	$(SRCDIR)/roll.c $(SRCDIR)/roll.h
	gcc -c $(SRCDIR)/roll.c -o $(BUILDDIR)/roll.o

prob.o:	$(SRCDIR)/prob.c $(SRCDIR)/prob.h
	gcc -c $(SRCDIR)/prob.c -o $(BUILDDIR)/prob.o

ui.o:	$(SRCDIR)/ui.c $(SRCDIR)/ui.h $(SRCDIR)/input.h
	gcc -c $(SRCDIR)/ui.c -o $(BUILDDIR)/ui.o

input.o:	$(SRCDIR)/input.c $(SRCDIR)/input.h
	gcc -c $(SRCDIR)/input.c -o $(BUILDDIR)/input.o

clean:
	rm -rf $(BUILDDIR)/*
	rm -rf $(BINDIR)/*