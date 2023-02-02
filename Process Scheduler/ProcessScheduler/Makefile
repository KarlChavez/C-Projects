lab4: main.o FCFS.o RR.o stcf.o sjf.o
	gcc -pthread -o lab4 main.o FCFS.o RR.o stcf.o sjf.o

FCFS.o: FCFS.c lab4.h
	gcc -c FCFS.c

lab4.o: main.c lab4.h
	gcc -c main.c

RR.o: RR.c lab4.h
	gcc -c RR.c

stcf.o: stcf.c lab4.h
	gcc -c stcf.c

sjf.o: sjf.c lab4.h
	gcc -c sjf.c

clean:
	rm -rf *.o lab4 lab4.zip
