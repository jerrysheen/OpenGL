#pragma once
#include <GL/glew.h>
#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLCheckError())

void GLClearError();
bool GLCheckError();

class Renderer
{
public :
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);

};

