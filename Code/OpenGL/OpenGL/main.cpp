#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main() {\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

const char* yellowFragmentShaderSource =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
"	FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";

int main() {

	//Init
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;

		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	// Shaders
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int yellowFragmentShader;
	yellowFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(yellowFragmentShader, 1, &yellowFragmentShaderSource, nullptr);
	glCompileShader(yellowFragmentShader);

	glGetShaderiv(yellowFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(yellowFragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	unsigned int yellowShaderProgram;
	yellowShaderProgram = glCreateProgram();
	glAttachShader(yellowShaderProgram, vertexShader);
	glAttachShader(yellowShaderProgram, yellowFragmentShader);
	glLinkProgram(yellowShaderProgram);

	glGetProgramiv(yellowShaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(yellowShaderProgram, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
	}

	float firstVertices[] = {
		 0.0f, 0.0f, 0.0f,
		 1.0f, 0.0f, 0.0f,
		 0.5f, 1.0f, 0.0f
	};

	float secondVertices[] = {
		 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-0.5f, -1.0f, 0.0f
	};

	unsigned int VAOs[2];
	unsigned int VBOs[2];
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBindVertexArray(VAOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstVertices), firstVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBindVertexArray(VAOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondVertices), secondVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glBindVertexArray(VAOs[0]);
		glDrawArrays(GL_TRIANGLES, 0, 3);


		glUseProgram(yellowShaderProgram);
		glBindVertexArray(VAOs[1]);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glfwTerminate();

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}