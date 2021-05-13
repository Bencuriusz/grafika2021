all:
	gcc -Iinclude source/*   -lSOIL -lglu32 -lopengl32 -lglut32 -lm -o beadando.exe 
linux:
	gcc -Iinclude source/*  -lSOIL -lGL -lGLU -lglut -lm -o beadando.exe 