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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

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
			-50.0f, -50.0f, 0.0f, 0.0f,
			50.0f, -50.0f, 1.0f, 0.0f,
			50.0f, 50.0f, 1.0f, 1.0f,
			 -50.0f, 50.0f, 0.0f, 1.0f
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
		// camera projection
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


		Shader shader("res/shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
		Texture texture("res/texture/Test.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		float r = 0.0f;
		/* Loop until the user closes the window */


		shader.Unbind();
		vb.Unbind();
		ib.Unbind();

		Renderer render;

		ImGui::CreateContext();
		ImGui_ImplGlfwGL3_Init(window, true);
		ImGui::StyleColorsDark();

		glm::vec3 translationA = glm::vec3(200, 0, 0);
		glm::vec3 translationB = glm::vec3(400, 200, 0);

		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			render.Clear();


			ImGui_ImplGlfwGL3_NewFrame();

			shader.Bind();
			//shader.SetUniform4f("u_Color", r, 0.5f, 0.8f, 1.0f);
			texture.Bind();

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				render.Draw(va, ib, shader);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				render.Draw(va, ib, shader);
			}


			//GLClearError();
			//glDrawArrays(GL_TRIANGLES, 0, 3);


			//ASSERT(GLCheckError());
			
			{

				ImGui::Text("Hello, world!");                           // Display some text (you can use a format string too)
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			ImGui::Render();
			ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

			r = r > 1.0f ? 0.0f : r + 0.03f;
			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}