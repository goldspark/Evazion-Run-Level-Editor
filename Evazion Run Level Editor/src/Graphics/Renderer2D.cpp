#include "Renderer2D.h"
#include <iostream>




std::string texturedVertexShader =
R"(
#version 450 core
layout(location = 0)in vec2 vPos;
layout(location = 1)in vec2 vTex;
layout(location = 2)in float vIndex;

out vec2 fTex;
out float fIndex;

void main(){
gl_Position = vec4(vPos, 0.0, 1.0);
fTex = vTex;
fIndex = vIndex;
}
)";

std::string texturedFragmentShader =
R"(
#version 450 core

out vec4 color;
in vec2 fTex;
in float fIndex;

uniform sampler2D texUnit[32];

void main(){ 
    int index = int(fIndex);
    color = texture(texUnit[index], fTex);
}
)";




struct VertexData {
	Vec2f position;
	Vec2f textureCoord;
	float texIndex;
};


GLuint whiteTexture;
GLuint textures[32];
int texturesIndex = 1;

VertexData* bufferData = nullptr;
int numberOfIndices = 0;
VertexData* bufferDataPtr = nullptr;









GoldSpark::Renderer2D::Renderer2D()
{


	bufferData = new VertexData[1000];
	

	GLuint indices[MAX_INDEX];

	int offset = 0;
	for (int i = 0; i < MAX_INDEX; i += 6)
	{
		indices[i] = offset;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset;

		offset += 4;
	}

	m_Program = new Shader(texturedVertexShader, texturedFragmentShader);


	m_Vao = new VertexArray();
	m_Vao->Bind();
	m_Vbo = new VertexBuffer(MAX_QUADS * sizeof(float));
	m_Ibo = new IndexBuffer(indices, sizeof(indices));

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, position));
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, textureCoord));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, sizeof(VertexData), (const void*)offsetof(VertexData, texIndex));


    // 1x1 white texture
	glCreateTextures(GL_TEXTURE_2D, 1, &whiteTexture);
	glBindTexture(GL_TEXTURE_2D, whiteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	uint32_t color = 0xffffffff;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1,0,GL_RGBA, GL_UNSIGNED_BYTE, &color);

	textures[0] = whiteTexture;
	for (size_t i = 1; i < MAX_TEXTURES; i++)
		textures[i] = 0;
	


	m_Program->Enable();
	auto loc = glGetUniformLocation(m_Program->GetID(), "texUnit");
	int samplers[32];
	for (int i = 0; i < MAX_TEXTURES; i++)
		samplers[i] = i;
	glUniform1iv(loc, MAX_TEXTURES, samplers);
	m_Program->Disable();

	
}

GoldSpark::Renderer2D::~Renderer2D()
{
	Free();
}

void GoldSpark::Renderer2D::Begin()
{
	//we set the ptr at the beginning
	bufferDataPtr = bufferData;
}

void GoldSpark::Renderer2D::End()
{
	GLsizeiptr size = (uint8_t*)bufferDataPtr - (uint8_t*)bufferData;
	m_Vbo->SetData(bufferData, size);
	
	
}

void GoldSpark::Renderer2D::Render()
{
	
	for (int i = 0; i < texturesIndex; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i]);
		
	}

	m_Program->Enable();
	m_Vao->Bind();
	glDrawElements(GL_TRIANGLES, numberOfIndices, GL_UNSIGNED_INT, nullptr);
	m_Program->Disable();

	
	numberOfIndices = 0;


	

}

void GoldSpark::Renderer2D::Free()
{
	delete m_Vao;
	delete m_Vbo;
	delete m_Ibo;
	delete m_Program;
	delete[] bufferData;
	sprites.clear();
}

void GoldSpark::Renderer2D::DrawQuad(const Vec2f& position, const Vec2f& size, const GLuint& texture)
{
	if (texturesIndex > 31 || numberOfIndices) {
		End();
		Render();
		Begin();
    }


	int currentIndex = 0;
	for (int i = 1; i < texturesIndex; i++) {
		if (textures[i] == texture) {
			currentIndex = i;
			break;
		}
	}

	if (currentIndex == 0) {
		currentIndex = texturesIndex;
		textures[texturesIndex] = texture;
		texturesIndex++;
	}

	bufferDataPtr->position = position;
	bufferDataPtr->textureCoord = Vec2f(0.0f, 0.0f);
	bufferDataPtr->texIndex = currentIndex;
	bufferDataPtr++;

	bufferDataPtr->position = { position.x + size.x, position.y };
	bufferDataPtr->textureCoord = Vec2f(1.0f, 0.0f);
	bufferDataPtr->texIndex = currentIndex;
	bufferDataPtr++;

	bufferDataPtr->position = { position.x + size.x, position.y + size.y };
	bufferDataPtr->textureCoord = Vec2f(1.0f, 1.0f);
	bufferDataPtr->texIndex = currentIndex;
	bufferDataPtr++;

	bufferDataPtr->position = { position.x, position.y + size.y };
	bufferDataPtr->textureCoord = Vec2f(0.0f, 1.0f);
	bufferDataPtr->texIndex = currentIndex;
	bufferDataPtr++;

	numberOfIndices += 6;

	
}

