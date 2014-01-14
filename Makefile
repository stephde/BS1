LIBDIR = "C:\Program Files (x86)\Windows Kits\8.0\Lib\win8\um\x86"
LIBS = "kernel32"
LINKFLAGS = -L$(LIBDIR) -l$(LIBS)



all: bmp_fractal.exe 

bmp_fractal.exe: bmp_fractal.c algorithm.h
	cl $(LINKFLAGS) bmp_fractal.c

clean: 
    @del /F /Q *.obj bmp_fractal.exe
