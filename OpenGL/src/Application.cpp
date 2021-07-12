#include "Renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;



    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

		glfwSwapInterval(1);
		if (glewInit() != GLEW_OK) {
			return -1;
		}

	{
		float positions[] = {
			100.0f, 100.0f, 0.0f, 0.0f,
			200.0f, 100.0f, 1.0f, 0.0f,
			200.0f, 200.0f, 1.0f, 1.0f,
			 100.0f, 200.0f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};



		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));
		
		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 0, 0));

		glm::mat4 mvp = proj * view * model;

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);
		Texture texture("res/texture/Test.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		float r = 0.0f;
		/* Loop until the user closes the window */


		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer render;
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
			texture.Bind();
			render.Draw(va, ib, shader);

			//GLClearError();
			//glDrawArrays(GL_TRIANGLES, 0, 3);


			//ASSERT(GLCheckError());
			


			r = r > 1.0f ? 0.0f : r + 0.03f;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}
    glfwTerminate();
    return 0;
}