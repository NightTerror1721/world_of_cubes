#include "support/GL.h"

#include <opengl/glut.h>
#include <iostream>
#include <string>


bool gl::check_errors()
{
	GLenum errCode;
	const GLubyte* errString;

	if ((errCode = glGetError()) != GL_NO_ERROR)
	{
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL error: " << reinterpret_cast<const char*>(errString) << std::endl;
		return false;
	}

	return true;
}
