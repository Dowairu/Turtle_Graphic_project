PROG = turtleprog
CC = clang
CFLAGS = -l SDL2 -l SDL2main -l SDL2_image -l shell32 -l turtlegraphics -o 
XLINKER = -Xlinker /subsystem:console  

turtleprog.exe: turtleprog.o turtlegraphics.lib
	@$(CC) $(PROG).c $(CFLAGS) $(PROG).exe $(XLINKER)

turtlegraphics.lib: turtle.o
	@llvm-lib /out:turtlegraphics.lib turtle.o	

turtle.o: turtle.c
	@$(CC) -c turtle.c

turtleprog.o: turtleprog.c
	@$(CC) -c $(PROG).c 