#version 330 core
layout (location = 0) in vec3 aPos;//从顶点属性中获取位置信息
layout (location = 1) in vec3 aColor;//从顶点属性中获取颜色信息

out vec3 ourColor;//需要输出的信息（输出给片段着色器）
out vec3 ourPosition;
uniform float xOffset;//定义一个偏移量

void main()
{
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
	ourPosition = aPos;//将位置信息赋给顶点着色器，并输出
    //ourColor = aColor;
}