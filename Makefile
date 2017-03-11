.PHONY: all clean
CC=clang
CFLAGS=-Wall
OBJECTS=unleash.o init.o cmdLineMgr.o cmdParser.o cmdScheduler.o cmdExecutor.o

all: $(OBJECTS)
	$(CC) $(CFLAGS) -o unleash $(OBJECTS)

unleash.o:
	$(CC) $(CFLAGS) -c src/unleash.c

init.o:
	$(CC) $(CFLAGS) -c src/init.c

cmdLineMgr.o:
	$(CC) $(CFLAGS) -c src/cmdLineMgr.c

cmdParser.o:
	$(CC) $(CFLAGS) -c src/cmdParser.c
	
cmdScheduler.o:
	$(CC) $(CFLAGS) -c src/cmdScheduler.c
	
cmdExecutor.o:	
	$(CC) $(CFLAGS) -c src/cmdExecutor.c

clean:
	rm $(OBJECTS) unleash