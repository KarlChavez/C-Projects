all: createThreads parallel1 parallel2 parallel3

createThreads: createThreads.o
	gcc -pthread -o createThreads createThreads.c

parallel1: parallel1.o
	gcc -pthread -o parallel1 parallel1.c

parallel2: parallel2.o
	gcc -pthread -o parallel2 parallel2.c

parallel3: parallel3.o
	gcc -pthread -o parallel3 parallel3.c

zipLab3:
	zip lab3.zip makefile readme *c
