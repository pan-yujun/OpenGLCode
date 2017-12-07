#version 330 core

in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;
uniform vec3 viewPos;
  
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{    
    //冯氏光照模型
	// ambient环境因子
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    // diffuse 漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
	// 镜面强度光
	vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float specularStrength = 0.5;
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;
            
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
    //float ambientStrength = 0.1; //环境因子
    //vec3 ambient = ambientStrength * lightColor;

    //vec3 result = ambient * objectColor;
   // FragColor = vec4(result, 1.0);
}