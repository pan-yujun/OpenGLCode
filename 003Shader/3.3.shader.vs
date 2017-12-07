#version 330 core
layout (location = 0) in vec3 aPos;//�Ӷ��������л�ȡλ����Ϣ
layout (location = 1) in vec3 aColor;//�Ӷ��������л�ȡ��ɫ��Ϣ

out vec3 ourColor;//��Ҫ�������Ϣ�������Ƭ����ɫ����
out vec3 ourPosition;
uniform float xOffset;//����һ��ƫ����

void main()
{
    gl_Position = vec4(aPos.x + xOffset, -aPos.y, aPos.z, 1.0);
	ourPosition = aPos;//��λ����Ϣ����������ɫ���������
    //ourColor = aColor;
}