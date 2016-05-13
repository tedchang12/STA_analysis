TARGET = a.out
CC = g++

SRCS = STA_analysis.cpp

OBJS = ${SRCS:.cpp=.o}
CFLAGS = -Wall -g -c
LFLAGS = -Wall -g

${TARGET}: ${OBJS}
	${CC} ${LFLAGS} ${OBJS} -o ${TARGET}

.cpp.o:
	${CC} ${CFLAGS} -o $@ $<

clean:
	rm -f core ${TARGET}; \
	rm *.o
run1:
	./${TARGET} input/cadcontest.v input/case1 19
	
run2:
	./${TARGET} input/cadcontest.v input/case2 15
run3:
	./${TARGET} input/cadcontest.v input/case3 6
run4:
	./${TARGET} input/cadcontest.v input/case4 3
run5:
	./${TARGET} input/cadcontest.v input/case5 25
run6:
	./${TARGET} input/cadcontest.v input/case6 3
