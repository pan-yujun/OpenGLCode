//实现功能：一个顶点着色器，两个片段着色器，两个着色器程序，
//一个片段着色器使用了uniform全局变量，并通过时间来改变其值
//一个片段着色器接受了顶点着色器传过来的颜色值，使用了索引缓冲对象
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//定义顶点着色器和片段着色器
//编写顶点着色器，然后编译这个着色器
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n" // 为片段着色器指定一个颜色输出
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n" // 注意我们如何把一个vec3作为vec4的构造器的参数
"   vertexColor = vec4(0.0, 1.0, 0.0, 1.0);\n" // 把输出变量设置为绿色
"}\0";
//编写片段着色器，然后编译这个着色器
const char *fragmentShaderSource = "#version 330 core\n"
"in vec4 vertexColor;\n" // 从顶点着色器传来的输入变量（名称相同、类型相同）
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vertexColor;\n"
"}\n\0";
//编写片段着色器2，然后编译这个着色器
const char *fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor; \n"// uniform全局变量
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

int main()
{
	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//配置GLFW。glfwWindowHint函数的第一个参数代表选项的名称，我们可以从很多以GLFW_开头的枚举值中选择；第二个参数接受一个整形，用来设置这个选项的值。
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//我们将主版本号(Major)和次版本号(Minor)都设为3。
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//我们同样明确告诉GLFW我们使用的是核心模式(Core-profile)。

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

	// 创建一个窗口对象
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();//释放之前的分配的所有资源
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//重绘窗口大小

	//初始化GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	// 创建并链接我们的着色器程序
	//编译顶点着色器
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);//创建一个着色器对象，用ID来引用的
	//把着色器源码(前文定义过)附加到着色器对象上
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);//第二个参数代表真正顶点着色器源码，在上文定义过
	glCompileShader(vertexShader);
	// 检测是否编译成功
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//片段着色器，同上
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//片段着色器2，同上
	int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
	glCompileShader(fragmentShader2);
	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// 链接着色器
	int shaderProgram = glCreateProgram();//创建着色器程序
	glAttachShader(shaderProgram, vertexShader);//着色器程序链接顶点着色器
	glAttachShader(shaderProgram, fragmentShader);//着色器程序链接片段着色器
	glLinkProgram(shaderProgram);//链接
	//检测链接是否成功
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	// 链接着色器2
	int shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vertexShader);
	glAttachShader(shaderProgram2, fragmentShader2);
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram2, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);//用完后删除顶点和片段着色器
	glDeleteShader(fragmentShader);//用完后删除顶点和片段着色器
	glDeleteShader(fragmentShader2);//用完后删除顶点和片段着色器

	//设置顶点数据
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

	unsigned int VBOs[2], VAOs[2], EBOs[2];//创建一个顶点数组对象VAO和顶点缓冲对象VBO,使用索引缓冲对象
	glGenVertexArrays(2, VAOs);
	glGenBuffers(2, VBOs);
	glGenBuffers(2, EBOs);//定义并初始化VBO，VAO，EBO---------2
	
	glBindVertexArray(VAOs[0]);//要想使用VAO,先绑定VAO，后面在着色器程序中直接使用VAO

	//3. 把顶点数组复制到缓冲中供OpenGL使用
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	// 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用-----------3
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

	//设置顶点属性指针，告诉OpenGL怎样查找数据
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	//第二个VAO，VBO，EBO
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);



	//note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	//请注意，这是允许的，打电话给glVertexAttribPointer注册VBO为顶点属性的绑定顶点缓冲对象，然后我们可以安全地解除绑定
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	//你可以打开VAO然后其他VAO称不会意外修改其他VAO，但这种情况很少发生。修改其他VAOs需要一种叫做glBindVertexArray因此我们一般不unbind VAOs（或VBOs），当它不是直接的必要。
	glBindVertexArray(0);


	// uncomment this call to draw in wireframe polygons.
	//注释掉这叫画线框图的多边形。
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//渲染循环
	while (!glfwWindowShouldClose(window))
	{
		//在这个函数中实现一些输入控制
		processInput(window);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// 渲染
		glUseProgram(shaderProgram);//使用着色器程序
		glBindVertexArray(VAOs[0]); //VBO的顶点数据（通过VAO间接绑定）
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//利用索引绘制矩形

		glUseProgram(shaderProgram2);//在调用uniform之前先激活着色器程序
		//随时间更新uniform值	
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram2, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		//glUseProgram(shaderProgram2);//使用着色器程序2
		glBindVertexArray(VAOs[1]); 
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//  检查并调用事件，交换缓冲
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//删除VAO，VBO，EBO
	glDeleteVertexArrays(2, VAOs);
	glDeleteBuffers(2, VBOs);
	glDeleteBuffers(2, EBOs);//-------4

	// 释放之前的分配的所有资源
	glfwTerminate();
	return 0;
}
// 在这个函数中实现一些输入控制
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
//重新绘制窗口是回调函数
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}