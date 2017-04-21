#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
	vec3 emission;
    float shininess;
}; 

in vec3 sampleExtraOutput; 
  
out vec4 color;
  
//uniform vec3 viewPos;
uniform Material material;

void main()
{
    // Ambient
    vec3 ambient = material.ambient;
  	
    // Diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(light.position - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // Specular
    //vec3 viewDir = normalize(viewPos - FragPos);
    //vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  
        
    //vec3 result = ambient + diffuse + specular + emission;
	vec3 result = material.ambient + material.emission + material.diffuse;
    color = vec4(material.diffuse, 1.0f);
} 