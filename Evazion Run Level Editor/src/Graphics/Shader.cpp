#include "Shader.h"



static const char defaultVertexShader[] =
"#version 400 core\n"
"layout(location=0)in vec3 vPosition;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(vPosition, 1.0);\n"
"}\n";

static const char defaultFragmentShader[] =
"#version 400 core\n"
"out vec4 color;\n"
"void main(){"
"color = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";








namespace GoldSpark {



	Shader::Shader()
	{
        programID = createProgram(defaultVertexShader, defaultFragmentShader);
	}

	Shader::Shader(const char* v, const char* f)
	{
        programID = createProgram(v, f);
	}

	Shader::~Shader()
	{
        Free();
	}

	void Shader::Enable()
	{
        glUseProgram(programID);
	}

	void Shader::Disable()
	{
        glUseProgram(0);
	}

	void Shader::Free()
	{
        glDeleteProgram(programID);
	}



	GLuint Shader::loadShader(GLenum shaderType, const char* shaderSource) {
        GLuint shader = glCreateShader(shaderType);
        if (shader) {
            glShaderSource(shader, 1, &shaderSource, nullptr);
            glCompileShader(shader);

            GLint compiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint infoLen = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

                if (infoLen) {
                    char* buf = new char[infoLen];
                    if (buf) {
                        glGetShaderInfoLog(shader, infoLen, NULL, buf);
                        std::cout << buf << std::endl;
                        delete[] buf;
                    }
                    glDeleteShader(shader);
                    shader = 0;
                }
            }
        }

        return shader;
    }


    GLuint Shader::createProgram(const char* vertexSource, const char* fragmentSource)
    {
        GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
        if (!vertexShader)
        {
            return 0;
        }

        GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
        if (!fragmentShader)
        {
            return 0;
        }

        GLuint program = glCreateProgram();

        if (program)
        {
            glAttachShader(program, vertexShader);
            glAttachShader(program, fragmentShader);
            glLinkProgram(program);
            GLint linkStatus = GL_FALSE;
            glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
            if (linkStatus != GL_TRUE)
            {
                GLint bufLength = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
                if (bufLength)
                {
                    char* buf = (char*)malloc(bufLength);
                    if (buf)
                    {
                        glGetProgramInfoLog(program, bufLength, NULL, buf);
                        std::cout << buf << std::endl;
                        free(buf);
                    }
                }
                glDeleteProgram(program);
                program = 0;
            }
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return program;
    }

}