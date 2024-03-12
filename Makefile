GLEW_LIBS = -lGLEW -lEGL -lGL -lGLU -lOpenGL 
GLFW_LIBS = -lglfw

OpenGL_Odyssey: main.c
	gcc -o OpenGL_Odyssey main.c $(GLEW_LIBS) $(GLFW_LIBS)

clean:
	rm OpenGL_Odyssey