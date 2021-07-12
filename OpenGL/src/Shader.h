#pragma once
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};
class Shader
{
private:
	unsigned int  m_RendererID;
	std::string m_FilePath; 
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	// Set uniform variable;
	void SetUniform4f(const std::string& name, float f1, float f2, float f3, float f4);
	void SetUniformMat4f(const std::string& name, glm::mat4& matrix);
	void SetUniform1i(const std::string& name, int value);
private:
	ShaderProgramSource ParseShader(const std::string& filepath);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int GetUniformLocation(const std::string &name);
};