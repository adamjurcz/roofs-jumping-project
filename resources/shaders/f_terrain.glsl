#version 330 core

out vec4 FragColor;

in float Height;
in vec2 texCoord;

uniform sampler2D texture0; //rock
uniform sampler2D texture1; //grass

void main(){
    const float border0 = 8.0f;
    const float border1 = 12.0f;

    vec4 texColorRock = texture(texture0, texCoord);
    vec4 texColorGrass = texture(texture1, texCoord);
    vec4 texColor;

    if(Height < border0){
        texColor = texColorRock;
    }
    else if (Height >= border0 && Height < border1){
        float diff = border1 - border0;
        float factorSecond = (Height - border0)/diff;
        float factorFirst = 1.0f - factorSecond;

        texColor = factorFirst * texColorRock + factorSecond * texColorGrass;
    }
    else{
        texColor = texColorGrass;
    }
    FragColor = texColor;
}