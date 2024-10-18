all:
	gcc -I src/include/SDL2 -L src/lib -o main main.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf