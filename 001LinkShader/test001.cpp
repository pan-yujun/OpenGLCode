//ʵ�ֹ��ܣ�һ��������ɫ��������Ƭ����ɫ����������ɫ������
//һ��Ƭ����ɫ��ʹ����uniformȫ�ֱ�������ͨ��ʱ�����ı���ֵ
//һ��Ƭ����ɫ�������˶�����ɫ������������ɫֵ��ʹ���������������
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//���嶥����ɫ����Ƭ����ɫ��
//��д������ɫ����Ȼ����������ɫ��
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n" // ΪƬ����ɫ��ָ��һ����ɫ���
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n" // ע��������ΰ�һ��vec3��Ϊvec4�Ĺ������Ĳ���
"   vertexColor = vec4(0.0, 1.0, 0.0, 1.0);\n" // �������������Ϊ��ɫ
"}\0";
//��дƬ����ɫ����Ȼ����������ɫ��
const char *fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n" // �Ӷ�����ɫ�����������������������ͬ��������ͬ��
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";
//��дƬ����ɫ��2��Ȼ����������ɫ��
const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor; \n"// uniformȫ�ֱ���
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

int main()
{
	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//����GLFW��glfwWindowHint�����ĵ�һ����������ѡ������ƣ����ǿ��ԴӺܶ���GLFW_��ͷ��ö��ֵ��ѡ�񣻵ڶ�����������һ�����Σ������������ѡ���ֵ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//���ǽ����汾��(Major)�ʹΰ汾��(Minor)����Ϊ3��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ͬ����ȷ����GLFW����ʹ�õ��Ǻ���ģʽ(Core-profile)��

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// ����һ�����ڶ���
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//�ͷ�֮ǰ�ķ����������Դ
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//�ػ洰�ڴ�С

	//��ʼ��GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// �������������ǵ���ɫ������
	//���붥����ɫ��
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//����һ����ɫ��������ID�����õ�
	//����ɫ��Դ��(ǰ�Ķ����)���ӵ���ɫ��������
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//�ڶ���������������������ɫ��Դ�룬�����Ķ����
	glCompileShader(vertexShader);
	// ����Ƿ����ɹ�
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Ƭ����ɫ����ͬ��
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Ƭ����ɫ��2��ͬ��
	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// ������ɫ��
	int shaderProgram = glCreateProgram();//������ɫ������
	glAttachShader(shaderProgram, vertexShader);//��ɫ���������Ӷ�����ɫ��
	glAttachShader(shaderProgram, fragmentShader);//��ɫ����������Ƭ����ɫ��
	glLinkProgram(shaderProgram);//����
	//��������Ƿ�ɹ�
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// ������ɫ��2
	int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);//�����ɾ�������Ƭ����ɫ��
	glDeleteShader(fragmentShader);//�����ɾ�������Ƭ����ɫ��
	glDeleteShader(fragmentShader2);//�����ɾ�������Ƭ����ɫ��

	//���ö�������
	float firstTriangle[] = {
		-0.9f, -0.9f, 0.0f,  // left 
		-0.9f, -0.2f, 0.0f,  // right
		-0.2f, -0.2f, 0.0f,  // top 
		-0.2f, -0.9f, 0.0f,  // top 
	};
	unsigned int indices1[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
		0, 2, 3   // second Triangle
	};
	float secondTriangle[] = {
		0.9f, 0.9f, 0.0f,  // left
		0.9f, 0.5f, 0.0f,  // right
		0.5f, 0.5f, 0.0f,   // top 
		0.5f, 0.9f, 0.0f   // top 
	};
	unsigned int indices2[] = {  // note that we start from 0!
		0, 1, 2,  // first Triangle
		0, 2, 3   // second Triangle
	};

	unsigned int VBOs[2], VAOs[2], EBOs[2];//����һ�������������VAO�Ͷ��㻺�����VBO,ʹ�������������
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(2, EBOs);//���岢��ʼ��VBO��VAO��EBO---------2
	
	glBindVertexArray(VAOs[0]);//Ҫ��ʹ��VAO,�Ȱ�VAO����������ɫ��������ֱ��ʹ��VAO

	//3. �Ѷ������鸴�Ƶ������й�OpenGLʹ��
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	// 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��-----------3
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	//���ö�������ָ�룬����OpenGL������������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//�ڶ���VAO��VBO��EBO
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	//note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//��ע�⣬��������ģ���绰��glVertexAttribPointerע��VBOΪ�������Եİ󶨶��㻺�����Ȼ�����ǿ��԰�ȫ�ؽ����
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//����Դ�VAOȻ������VAO�Ʋ��������޸�����VAO��������������ٷ������޸�����VAOs��Ҫһ�ֽ���glBindVertexArray�������һ�㲻unbind VAOs����VBOs������������ֱ�ӵı�Ҫ��
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//ע�͵���л��߿�ͼ�Ķ���Ρ�
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//��Ⱦѭ��
	while (!glfwWindowShouldClose(window))
	{
		//�����������ʵ��һЩ�������
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// ��Ⱦ
		glUseProgram(shaderProgram);//ʹ����ɫ������
		glBindVertexArray(VAOs[0]); //VBO�Ķ������ݣ�ͨ��VAO��Ӱ󶨣�
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//�����������ƾ���

		glUseProgram(shaderProgram2);//�ڵ���uniform֮ǰ�ȼ�����ɫ������
		//��ʱ�����uniformֵ	
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//glUseProgram(shaderProgram2);//ʹ����ɫ������2
		glBindVertexArray(VAOs[1]); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//  ��鲢�����¼�����������
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//ɾ��VAO��VBO��EBO
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(2, EBOs);//-------4

	// �ͷ�֮ǰ�ķ����������Դ
	glfwTerminate();
	return 0;
}
// �����������ʵ��һЩ�������
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//���»��ƴ����ǻص�����
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}