#version 330 core
out vec4 FragColor;//��Ƭ����ɫ�������ɫ��Ϣ

//in vec3 ourColor;
in vec3 ourPosition;//�Ӷ�����ɫ����ȡλ����Ϣ

void main()
{
    //FragColor = vec4(ourColor, 1.0f);
	FragColor = vec4(ourPosition, 1.0f);
}