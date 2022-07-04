
.PHONY: tester

CC      = g++
CFLAGS  += -Wall -Wextra
OBJS = inip.o iniparser.o dictionary.o
SRCS = src/inip.cpp src/dictionary.c src/iniparser.c

tester: cpplib.a
	${CC} ${CFLAGS} -o initest src/initester.cpp -L. -linip

cpplib.a: cpplib
	ar rcs libinip.a ${OBJS} 
	rm -R ${OBJS}

cpplib: src/inip.cpp
	${CC} ${CFLAGS} -c ${SRCS}

clean:
	rm -R ${OBJS}
	rm -R libinip.a
	rm -R initest