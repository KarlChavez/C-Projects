#Braeden J

all: compile lab4.zip clean

compile: lab4

lab4: main.o Stack1.o Stack2.o
	gcc -O -pg -o $@ $^

lab4.zip: makefile *.c *.h readme
	zip lab4.zip makefile *.c *.h readme Stack1out Stack2out gmon.out

# Compile the c file into an o file.
# You'll want to change this line for the lab.
%.o:%.c *.h
	gcc -ansi -pedantic -Wimplicit-function-declaration -Wreturn-type -O -pg -c $< -o $@

#Remove all intermediate files.
clean:
	rm -rf *.o


#These two are shorthand because typing less characters is cool!:
z: lab4.zip

c: clean
