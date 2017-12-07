#version 330 core
out vec4 FragColor;//从片段着色器输出颜色信息

//in vec3 ourColor;
in vec3 ourPosition;//从顶点着色器获取位置信息

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
	FragColor = vec4(ourPosition, 1.0f);
}