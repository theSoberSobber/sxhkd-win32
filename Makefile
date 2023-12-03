DEBUG = -DDEBUG
CFLAGS = -w -Wall -Os ${DEBUG}
LDFLAGS = -s -mwindows
CC = gcc

SRC = main.c
OBJ = ${SRC:.c=.o}

all: options sxhkd-win32

options:
		@echo sxhkd-win32 build options:
		@echo "CFLAGS   = ${CFLAGS}"
		@echo "LDFLAGS  = ${LDFLAGS}"
		@echo "CC       = ${CC}"

sxhkd-win32: ${OBJ}
		@echo "${CC} -o $@"
		@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
		rm -f ${OBJ} sxhkd-win32
