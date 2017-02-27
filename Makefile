PROGRAM	=	moct
SRCS	=	input.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-O2 -pipe -s -march=native
CC	=	gcc
PREFIX 	=	/usr/local/bin

.PHONY: all clean

all:$(PROGRAM)
$(PROGRAM):$(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
install: $(PROGRAM)
	install -sv $< $(PREFIX)
uninstall: $(PROGRAM)
	$(RM) $(PREFIX)/$(PROGRAM)

clean:
	$(RM) $(OBJS) $(PROGRAM)
