CXX = g++
SRC = src/tsort.cpp src/sorting.cpp
OBJ = ${SRC:.cpp=.o}
LDFLAGS = -lncurses
PREFIX = /usr/local

tsort: ${OBJ}
	${CXX} -o $@ $^ ${LDFLAGS}

clean:
	rm -f ${OBJ} tsort

install: tsort
	mkdir -p ${DESTDIR}${PREFIX}/bin
	install -m 0755 tsort ${DESTDIR}${PREFIX}/bin/tsort

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/tsort

.PHONY: clean install uninstall