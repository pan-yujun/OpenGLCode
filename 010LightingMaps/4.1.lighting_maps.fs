#version 330 core
out vec4 FragColor;

struct Material {
                       //漫反射贴图
    sampler2D diffuse;//注意sampler2D是所谓的不透明类型(Opaque Type)，也就是说我们不能将它实例化，只能通过uniform来定义它
    //vec3 specular;  
	sampler2D specular;//镜面光贴图
	sampler2D emission;//放射光贴图
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
	//vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));//将木质（漫反射）显示镜面光
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb; //使用了镜面光贴图
	//vec3 specular = light.specular * spec * (vec3(1.0) - vec3(texture(material.specular, TexCoords))); // here we inverse the sampled specular color. Black becomes white and white becomes black.
        
    // 放射性光
    vec3 emission = texture(material.emission, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
} 