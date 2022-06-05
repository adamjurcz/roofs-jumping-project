#version 330 core
in vec3 Normal;
in vec3 FragPosition;

out vec4 FragColor;
  
uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;


in vec2 texCoord;
uniform sampler2D texture0;

const float ambientStrength = 0.2f;
const float specularStrength = 0.5f;

void main()
{   
    vec3 ambient = ambientStrength * lightColor;                            //ambient

    vec3 norm = normalize(Normal);                                          //normalizujemy wektor normalny obiektu  -- diffuse
    vec3 lightDirect = normalize(lightPos - FragPosition);                  //obliczamy roznice wektorow pozycji swiatla i wektora pozycji obiektu jako wektor od konca fragPos do konca lightPos 
    float diff = max(dot(norm, lightDirect), 0.0f);                         //liczymy il. wektorowy tzn. jezeli kat pomiedzy normalna i kierunkiem swiatla rosnie <=> maleje cosa dzieki normalizacji- slabsze swiatlo  
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPosition);                       //specular
    vec3 reflectDir = reflect(-lightDirect, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor;


    vec3 result = (ambient+diffuse+specular) * objectColor;
    FragColor = vec4(result, 1.0) * texture(texture0, texCoord);
}