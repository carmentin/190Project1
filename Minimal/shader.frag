#version 330 core
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
	vec3 emission;
    float shininess;
}; 

in vec3 mynormal;
in vec4 myvertex;
  
out vec4 color;
  
uniform Material material;
uniform mat4 view;
uniform mat4 model;
uniform vec3 eyepos;

vec4 computeLight(const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess){
	float nDotL = dot(normal, direction);
	vec4 lambert = mydiffuse * lightcolor * max(nDotL, 0.f);
	
	float nDotH = dot(normal, halfvec);
	vec4 phong = myspecular * lightcolor * pow(max(nDotH, 0.f), myshininess);

	vec4 retval = lambert + phong;
	return retval;
}

void main()
{
	mat4 modelview = view * model;
	/*
    vec4 finalColor = vec4(material.ambient,1) + vec4(material.emission,1);
	const vec3 eyepos = vec3(0, 0, 0);
	vec4 v = modelview * myvertex;
	vec3 mypos = v.xyz/ v.w;
	vec3 eyedirn = normalize(eyepos - mypos);

	mat3 nmatrix = mat3(transpose(inverse(modelview)));
	vec3 normal = normalize(nmatrix * mynormal);
	vec4 col;
	vec3 direction, halfi;

	//hardcoded directional light at (0,10,0);
	vec3 lightpos = vec3(0.f, 5.f, 5.f);
	vec4 lightcol = vec4(0.7f, 0.7f, 0.4f, 1.f);
	direction = normalize(lightpos);
	halfi = normalize(direction + eyedirn);
	col = computeLight(direction, lightcol, normal, halfi, vec4(material.diffuse,1), vec4(material.specular,1), material.shininess);
	finalColor += col;

	color = finalColor;*/

	vec3 lightcol = vec3(0.7f, 0.7f, 0.7f);
	vec3 lightpos = vec3(0.0f, 5.0f, 5.0f);
	float ambientStrength = 0.3f;
	vec3 ambient = ambientStrength * lightcol;

	vec3 norm = normalize(mynormal);
	vec4 v = modelview * myvertex;
	vec3 fragpos = v.xyz / v.w; 
	vec3 lightdir = normalize(lightpos - myvertex.xyz);
	float diff = max(dot(norm, lightdir), 0.0f);
	vec3 diffuse = diff * lightcol;

	float specularStrength = 0.5f;
	vec3 viewdir = normalize(eyepos - fragpos);
	vec3 reflectdir = reflect(-lightdir, norm);
	float spec = pow(max(dot(viewdir, reflectdir), 0.0f), 32);
	vec3 specular = specularStrength * spec * lightcol;

	vec3 result = (ambient + diffuse + specular) * material.diffuse;
	color = vec4(result, 1.0f);

   // color = vec4(material.diffuse, 1.0f);


} 