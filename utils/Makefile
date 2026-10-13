# $Header: /usr/src/local/franz/utils/RCS/Makefile,v 1.3 88/10/14 14:25:41 sklower Exp $
# $Locker:  $

CFLAGS = -std=c90 -Wno-implicit-function-declaration
CC = cc 

LibDir = /tmp/usr/lib/lisp
AllSrc = Makefile append.c tackon.c divide.c

AllObj = ${LibDir}/append ${LibDir}/tackon ${LibDir}/divide

all: ${LibDir}/append ${LibDir}/tackon ${LibDir}/divide

${LibDir}/append: append.c
	echo here $(CC) $(CFLAGS)
	mkdir -p ${LibDir}
	$(CC) $(CFLAGS) -O -o ${LibDir}/append  -I../franz/h append.c

${LibDir}/tackon: tackon.c
	mkdir -p ${LibDir}
	$(CC) $(CFLAGS) -O -o ${LibDir}/tackon -I../franz/h tackon.c

${LibDir}/divide: divide.c
	mkdir -p ${LibDir}
	$(CC) $(CFLAGS) -O -o ${LibDir}/divide -I../franz/h divide.c

copysource: ${AllSrc}
	(tar cf - ${AllSrc} | (cd ${CopyTo} ; tar xf -))


scriptcatall: ${AllSrc}
	@../scriptcat . utils ${AllSrc}


clean:
	rm ${AllObj}
