all: Color.o Assignment3.o Vector4.o colorKernel.o geometryKernel.o interpolator.o Ray.o rayTracer.o
	g++ Color.o Assignment3.o Vector4.o colorKernel.o geometryKernel.o interpolator.o Ray.o rayTracer.o -lglut -lGLU -lGL -o Assignment3.out
Color: Color.cpp Color.h
	g++ -c Color.cpp -lglut -lGLU -lGL
Vector4: Vector4.cpp Vector4.h
	g++ -c Vector4.cpp -lglut -lGLU -lGL
colorKernel: colorKernel.cpp colorKernel.h
	g++ -c colorKernel.cpp -lglut -lGLU -lGL
geometryKernel: geometryKernel.cpp geometryKernel.h
	g++ -c geometryKernel.cpp -lglut -lGLU -lGL
interpolator: interpolator.cpp interpolator.h
	g++ -c interpolator.cpp -lglut -lGLU -lGL
Ray: Ray.cpp Ray.h
	g++ -c Ray.cpp -lglut -lGLU -lGL
rayTracer: rayTracer.cpp rayTracer.h
	g++ -c rayTracer.cpp -lglut -lGLU -lGL
Assignment3: Assignment3.cpp
	g++ -c Assignment3.cpp -lglut -lGLU -lGL
clean:
	rm -rf *.o Assignment3.out
