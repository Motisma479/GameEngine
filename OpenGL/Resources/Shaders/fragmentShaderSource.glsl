#version 330 core

#define MAX_LIGHT 16

out vec4 FragColor;

in vec2 TexCoord;

in vec3 FragPos;
in vec3 Normal;

struct Material
{
	vec3  ambient;
	vec3  diffuse;
	vec3  specular;
	vec3  emisive;
	float shininess;
};

struct DirLight
{
	vec3 p_direction;

	vec3 p_ambientColor;
	vec3 p_diffuseColor;
	vec3 p_specularColor;
};

struct PointLight
{
	vec3 p_position;

	float p_constant;
	float p_linear;
	float p_quadratic;

	vec3 p_ambientColor;
	vec3 p_diffuseColor;
	vec3 p_specularColor;
};

uniform DirLight dirLight[MAX_LIGHT];
uniform PointLight pointLight[MAX_LIGHT];

uniform Material material;

uniform vec3 viewPos;

uniform sampler2D texture1;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize( light.p_direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading



	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);



	// combine results
	vec3 ambient  = light.p_ambientColor  * material.diffuse;
	vec3 diffuse = light.p_diffuseColor * diff * material.diffuse;
	vec3 specular = light.p_specularColor * spec;
	
	return (ambient + diffuse + specular); 
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{
	vec3 lightDir = normalize(light.p_position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading




	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);




	// attenuation
	float distance = length(light.p_position - fragPos);
	float attenuation = 1.0 / (light.p_constant + light.p_linear * distance +
		light.p_quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.p_ambientColor * material.diffuse;
	vec3 diffuse = light.p_diffuseColor * diff * material.diffuse;
	vec3 specular = light.p_specularColor * spec * material.specular;
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}


void main()
{
	vec3 output = vec3(0.0);
	vec3 normal = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	//vec3 lightDir = normalize(lightPos - FragPos); // 1 check, 2 Check	

		output += CalcDirLight(dirLight[0], normal, viewDir);
	for(int i = 0; i < MAX_LIGHT; i++)
	{
		//output += CalcPointLight(pointLight[i], normal, FragPos, viewDir);
	}


	FragColor = vec4(output, 1.0) * texture(texture1, TexCoord);
	
	//FragColor = texture(texture1, TexCoord);
}