include config.mk
SRC = tm.c
OBJ = ${SRC:.c=.tmp.c}

all: prepros tm pospros

prepros: ${SRC}
	mkdir -p ${JSON_PATH}
	touch ${OBJ}
	sed 's|JSONPATH|${JSON_PATH}|g' < tm.c > ${OBJ} 

tm: ${OBJ} 
	${CC} -o $@ ${OBJ} ${CFLAGS} ${LDFLAGS}

pospros: 
	rm ${OBJ}

clean:
	rm -f tm
	rm -f tm.tmp.c

install: all
	mkdir -p ${LOCAL_DIR}/bin
	cp -f tm ${LOCAL_DIR}/bin
	chmod 755 ${LOCAL_DIR}/bin/tm

.PHONY: all install clean

