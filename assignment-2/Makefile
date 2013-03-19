all: ifs.o Assignment2.o Vector4.o Matrix4.o transformWorld.o transformObject.o transformCamera.o render.o test.o
	g++ ifs.o Assignment2.o Vector4.o Matrix4.o transformWorld.o transformObject.o transformCamera.o render.o test.o -lglut -lGLU -lGL  -lglui -o Assignment2.out
ifs: ifs.c ifs.h
	gcc -c ifs.c -lglut -lGLU -lGL -lglui
Vector4: Vector4.cpp Vector4.h
	g++ -c Vector4.cpp -lglut -lGLU -lGL -lglui
Matrix4: Matrix4.cpp Matrix4.h
	g++ -c Matrix4.cpp -lglut -lGLU -lGL -lglui
transformWorld: transformWorld.cpp transformWorld.h
	g++ -c transformWorld.cpp -lglut -lGLU -lGL -lglui
transformCamera: transformCamera.cpp transformCamera.h
	g++ -c transformCamera.cpp -lglut -lGLU -lGL -lglui
transformObject: transformObject.cpp transformObject.h
	g++ -c transformObject.cpp -lglut -lGLU -lGL -lglui
render: render.cpp render.h
	g++ -c render.cpp -lglut -lGLU -lGL -lglui
Assignment2: Assignment2.cpp
	g++ -c Assignment2.cpp -lglut -lGLU -lGL -lglui
clean:
	rm -rf *.o Assignment2.out
