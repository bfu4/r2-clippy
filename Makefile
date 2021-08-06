CFLAGS		= -O2 -std=c99 -Wall -Wextra 
TARGET		= r2-clippy
OBJECTS		=  r2-exported-util.o r2-clippy.o
BUILD_DIR 	= build


strip: $(TARGET)
	strip $(TARGET)

all: $(TARGET)

$(TARGET): ${OBJECTS}
	${CC} -o $@ ${OBJECTS}


.c.o: 
	${CC} $(CFLAGS) -c $<

.PHONY: clean
clean:
	@rm -f *.o $(TARGET)
