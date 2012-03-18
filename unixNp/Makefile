include ../Make.defines

PROGS =	simpleCliServ/simCli simpleCliServ/simServ

all:	${PROGS}

simCli:	simCli.o
		${CC} ${CFLAGS} -o $@ ntpCli.o ${LIBS}
simServ: simServ.o
		${CC} ${CFLAGS} -o $@ ntpCli.o ${LIBS}
clean:
		rm -f ${PROGS} ${CLEANFILES}
