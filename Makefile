GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw

OBJ = main.o Logger.o

OpenGL_Odyssey: $(OBJ)
	g++ -o $@ $(OBJ) $(GLEW_LIBS) $(GLFW_LIBS)

%.o: %.cc
	g++ -c $<

clean:
	rm OpenGL_Odyssey $(OBJ)