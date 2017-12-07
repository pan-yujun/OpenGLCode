#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
    //FragColor = vec4(ourColor, 1.0);//将颜色属性赋给片段着色器输出
	//FragColor = texture(texture1, TexCoord);//将纹理属性赋给片段着色器输出
	//FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);//利用mixValue来改变混合效果,需先定义
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
}