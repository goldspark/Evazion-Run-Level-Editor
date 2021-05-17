#include "DebugDraw.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "../display/State.h"


static const char debugVertexShader[] =
"#version 400 core\n"
"layout(location=0)in vec2 vPosition;\n"
"layout(location=1)in vec3 vColor;\n"
"out vec3 fColor;\n"
"uniform mat4 mvp;\n"
"void main()\n"
"{\n"
" gl_Position = mvp * vec4(vPosition, 0.0, 1.0);\n"
" fColor = vColor;\n"
"}\n";

static const char debugFragmentShader[] =
"#version 400 core\n"
"out vec4 color;\n"
"in vec3 fColor;\n"
"void main(){"
"color = vec4(fColor, 1.0);\n"
"}\n";



GoldSpark::VertexData* bufferData;

GLuint indices[] = { 0, 1, 2, 2, 3, 0 };

GoldSpark::DebugDraw::DebugDraw()
{

	bufferData = new VertexData[4];
	

	shader = new Shader(debugVertexShader, debugFragmentShader);

	glm::mat4 cameraOrthoMat = glm::mat4(1.0f);
	cameraOrthoMat = glm::ortho(0.0f, 100.0f, 0.0f, 100.0f);

	glUseProgram(shader->GetID());
	if(GoldState::camera != nullptr)
	shader->UploadMat4f(glm::value_ptr(GoldState::camera->GetCameraMatrix()));
	

	GLuint indices[] = { 0, 1, 2, 2, 3, 0 };


	vao = new VertexArray();
	vao->Bind();
	vbo = new VertexBuffer(5 * 4 * sizeof(float));
	ibo = new IndexBuffer(indices, 6 * sizeof(GLuint));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, color));


	

}



GoldSpark::DebugDraw::~DebugDraw()
{
	
	delete vao;
	delete vbo;
	delete ibo;
	delete shader;
	delete[] bufferData;
}





void GoldSpark::DebugDraw::DrawDebugQuad(const Math::Vec2f& pos, const Math::Vec2f& size, const Math::Vec3f& color)
{
	
	

	bufferData[0].position = {pos.x, pos.y};
	bufferData[0].color = {color.x, color.y, color.z};
	bufferData[1].position = { pos.x + size.x, pos.y };
	bufferData[1].color = { color.x, color.y, color.z };
	bufferData[2].position = { pos.x + size.x, pos.y + size.y };
	bufferData[2].color = { color.x, color.y, color.z };
	bufferData[3].position = { pos.x, pos.y + size.y };
	bufferData[3].color = { color.x, color.y, color.z };


	
	

	vbo->SetData(bufferData, 5 * 4 * sizeof(float));
	

	shader->Enable();

	
		


	vao->Bind();
	if (GoldState::camera != nullptr) {
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3{ GoldState::moveCameraLeftRight, 0.0f, 0.0f }) * glm::scale(glm::mat4(1.0f), glm::vec3{ 1.0f, 1.0f, 1.0f });
		glm::mat4 result = glm::mat4(1.0f);
		result = GoldState::camera->GetCameraMatrix() * view;
		shader->UploadMat4f(glm::value_ptr(result));
	}
	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glDrawElements(GL_LINE_STRIP, (GLsizei)(sizeof(indices) / sizeof(indices[0])), GL_UNSIGNED_INT, nullptr);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	vao->Unbind();
	shader->Disable();

	

}






