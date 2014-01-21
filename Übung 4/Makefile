all: aufg42_first aufg42_buddy

aufg42_buddy: aufg42.o memory.c
	gcc  -DBUDDY -o aufg42_buddy aufg42.c memory.c

aufg42_first: aufg42.o memory.c
	gcc  -DFIRST -o aufg42_first aufg42.c memory.c
clean:
	rm -rf *.o
	rm -rf aufg42_first
	rm -rf aufg42_buddy
