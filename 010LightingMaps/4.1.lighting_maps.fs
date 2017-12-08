#version 330 core
out vec4 FragColor;

struct Material {
                       //��������ͼ
    sampler2D diffuse;//ע��sampler2D����ν�Ĳ�͸������(Opaque Type)��Ҳ����˵���ǲ��ܽ���ʵ������ֻ��ͨ��uniform��������
    //vec3 specular;  
	sampler2D specular;//�������ͼ
	sampler2D emission;//�������ͼ
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoords;
  
uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    // ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//��ľ�ʣ������䣩��ʾ�����
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb; //ʹ���˾������ͼ
	//vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoords))); // here we inverse the sampled specular color. Black becomes white and white becomes black.
        
    // �����Թ�
    vec3 emission = texture(material.emission, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 