.PHONY = output

CC = g++

LINKERFLAG = -lncurses -g -std=c99


output: text.o page.o line.o
	${CC} text.o page.o line.o ${LINKERFLAG} -o editor.out

text.o: text.cpp text.h
	${CC} -c text.cpp

page.o: page.cpp page.h
	${CC} -c page.cpp

line.o: line.cpp line.h
	${CC} -c line.cpp

clean:
	rm *.o editor.out

clntxt:
	rm *.txt