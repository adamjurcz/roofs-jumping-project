#version 330 core

#define ARR_SIZE 2

in vec3 Normal;
in vec3 FragPosition;
in vec2 texCoord;

out vec4 FragColor;
  
uniform vec3 viewPos;
uniform vec3 lightPos[ARR_SIZE];
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 sunDirect;


uniform sampler2D texture0;

const float ambientStrength = 0.12f;
const float specularStrength = 0.25f;


vec3 ambientPoint(){
    vec3 _ambient = ambientStrength * lightColor;                           //ambient
    return _ambient;
}

vec3 diffusePoint(vec3 lightPos){
    vec3 norm = normalize(Normal);                                          //normalizujemy wektor normalny obiektu  
    vec3 lightDirect = normalize(lightPos - FragPosition);                  //obliczamy roznice wektorow pozycji swiatla i wektora pozycji obiektu jako wektor od konca fragPos do konca lightPos 
    float diff = max(dot(norm, lightDirect), 0.0f);                         //liczymy il. wektorowy tzn. jezeli kat pomiedzy normalna i kierunkiem swiatla rosnie <=> maleje cosa dzieki normalizacji- slabsze swiatlo  
    vec3 _diffuse = diff * lightColor;
    return _diffuse;
}

vec3 specularPoint(vec3 lightPos){
    vec3 norm = normalize(Normal);                                          //specular
    vec3 lightDirect = normalize(lightPos - FragPosition);  
    vec3 viewDir = normalize(viewPos - FragPosition);                       
    vec3 reflectDir = reflect(-lightDirect, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 _specular = specularStrength * spec * lightColor;
    return _specular;
}

float lightPowerPoint(vec3 lightPos){
    const float constant = 1.0f;
    const float linear = 0.045f;
    const float quadr = 0.0075f;

    float dist = length(lightPos - FragPosition);

    float _attenuation = 1.0f / (constant + linear * dist + quadr * (dist * dist));
    return _attenuation;
}


vec3 ambientDirect(){
    vec3 _ambient = ambientStrength * lightColor;                           //ambient
    return _ambient;
}

vec3 diffuseDirect(){
    vec3 norm = normalize(Normal);                                          
    vec3 lightDirect = normalize(-sunDirect);                  
    float diff = max(dot(norm, lightDirect), 0.0f);                         
    vec3 _diffuse = diff * lightColor;
    return _diffuse;
}

vec3 specularDirect(){
    vec3 norm = normalize(Normal);                                          //specular
    vec3 lightDirect = normalize(-sunDirect);  
    vec3 viewDir = normalize(viewPos - FragPosition);                       
    vec3 reflectDir = reflect(-lightDirect, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 _specular = specularStrength * spec * lightColor;
    return _specular;
}


void main(){
    vec3 _ambientDir = ambientDirect();
    vec3 _diffuseDir = diffuseDirect();
    vec3 _specularDir = specularDirect();

    vec3 result = _ambientDir + _diffuseDir + _specularDir;

    vec3 _ambientPoint = ambientPoint();
    for(int i = 0; i < ARR_SIZE; i++){
        vec3 _diffusePoint = diffusePoint(lightPos[i]);
        vec3 _specularPoint = specularPoint(lightPos[i]);
        float _lightPowerPoint = lightPowerPoint(lightPos[i]);
        
        result += _ambientPoint * _lightPowerPoint + _diffusePoint * _lightPowerPoint + _specularPoint * _lightPowerPoint;
    }

    FragColor = vec4(result, 1.0f) * texture(texture0, texCoord);
}

//////////////////////////////////////////////////////////////////////////////

/*
const float ambientStrength = 0.1f;
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

*/


/*
#version 330 core
in vec3 Normal;
in vec3 FragPosition;
in vec2 texCoord;

out vec4 FragColor;
  
uniform vec3 viewPos;
//uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 sunDirect;


struct PointLight{
    vec3 lightPos;

    float const;
    float linear;
    float quadratic;
};

struct DirectLight{
    

};

uniform sampler2D texture0;

const float ambientStrength = 0.3f;
const float specularStrength = 0.5f;



/*
vec3 ambientPoint(){
    vec3 _ambient = ambientStrength * lightColor;                           //ambient
    return _ambient;
}

vec3 diffusePoint(){
    vec3 norm = normalize(Normal);                                          //normalizujemy wektor normalny obiektu  
    vec3 lightDirect = normalize(lightPos - FragPosition);                  //obliczamy roznice wektorow pozycji swiatla i wektora pozycji obiektu jako wektor od konca fragPos do konca lightPos 
    float diff = max(dot(norm, lightDirect), 0.0f);                         //liczymy il. wektorowy tzn. jezeli kat pomiedzy normalna i kierunkiem swiatla rosnie <=> maleje cosa dzieki normalizacji- slabsze swiatlo  
    vec3 _diffuse = diff * lightColor;
    return _diffuse;
}

vec3 specularPoint(){
    vec3 norm = normalize(Normal);                                          //specular
    vec3 lightDirect = normalize(lightPos - FragPosition);  
    vec3 viewDir = normalize(viewPos - FragPosition);                       
    vec3 reflectDir = reflect(-lightDirect, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 _specular = specularStrength * spec * lightColor;
    return _specular;
}
*/
/*
vec3 ambientDirect(){
    vec3 _ambient = ambientStrength * lightColor;                           //ambient
    return _ambient;
}

vec3 diffuseDirect(){
    vec3 norm = normalize(Normal);                                          
    vec3 lightDirect = normalize(-sunDirect);                  
    float diff = max(dot(norm, lightDirect), 0.0f);                         
    vec3 _diffuse = diff * lightColor;
    return _diffuse;
}

vec3 specularDirect(){
    vec3 norm = normalize(Normal);                                          //specular
    vec3 lightDirect = normalize(-sunDirect);  
    vec3 viewDir = normalize(viewPos - FragPosition);                       
    vec3 reflectDir = reflect(-lightDirect, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 _specular = specularStrength * spec * lightColor;
    return _specular;
}


void main(){
    vec3 ambientDir = ambientDirect();
    vec3 diffuseDir = diffuseDirect();
    vec3 specularDir = specularDirect();


    
    vec3 result = ambientDir + diffuseDir + specularDir;
    FragColor = vec4(result, 1.0f) * texture(texture0, texCoord);



}

*/