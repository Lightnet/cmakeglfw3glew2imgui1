// https://learnopengl.com/Getting-started/Hello-Window
#define GLFW_INCLUDE_GL_3

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {	
	if( GL_TRUE != glfwInit()){
		//std::cerr << "Error initialising glfw" << std::endl;
	}

	// Window and context; we want OpenGL 4.5
	//glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
	//glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 5 );
	//glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
	//glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	

	GLFWwindow *window{ glfwCreateWindow( 800, 600, "Hello world", nullptr, nullptr ) };
	if( NULL == window )
		std::cerr << "Could not create glfw window\n" << std::endl;
	glfwMakeContextCurrent( window );
	glewExperimental = true;
	GLenum res{ glewInit() };
	if( GLEW_OK != res ) {
		std::cerr << glewGetErrorString( res ) << std::endl;
		std::cerr << "Error initialising glew" << std::endl;
	}

	GLint vmajor, vminor;
	glGetIntegerv( GL_MAJOR_VERSION, &vmajor );
	glGetIntegerv( GL_MINOR_VERSION, &vminor );
	std::cout << "OpenGL version " << vmajor << '.' << vminor << '\n';

  // render loop
	while(!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//...

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
  
  // clean up
	glfwDestroyWindow( window );
	glfwTerminate();

}	// ctor