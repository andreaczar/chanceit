chanceit:	controller.o roll.o prob.o ui.o
	gcc -o chanceit roll.o prob.o ui.o controller.o

controller.o:	roll.h ui.h prob.h
	gcc -c controller.c

roll.o:	roll.c roll.h
	gcc -c roll.c

prob.o:	prob.c prob.h
	gcc -c prob.c

ui.o:	ui.c ui.h
	gcc -c ui.c