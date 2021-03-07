CC=gcc
CFLAGS=-g
INCLUDES= -I. -I./include
SRCDIR=./src
SRCS=$(wildcard $(SRCDIR)/*.c) 
OBJS=$(SRCS:.c=.o)
MAIN=pixedit
PKG=`pkg-config --cflags gtk+-3.0`
LIB=`pkg-config --libs gtk+-3.0`

.PHONY:	depend clean

all:	$(MAIN)
	@echo  compiled with

$(MAIN):$(OBJS) 
	$(CC) $(PKG) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LIB)

.c.o:
	$(CC) $(PKG) $(CFLAGS) $(INCLUDES) -c $<  -o $@ $(LIB)

clean:
	$(RM) *.o *~ $(MAIN)

depend:	$(SRCS)
	makedepend $(INCLUDES) $^

