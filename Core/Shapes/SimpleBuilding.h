#ifndef SIMPLEBUILDING_H
#define SIMPLEBUILDING_H

#include "../Shaders/ShaderProgram.h"
#include "../Scene/Textures.h"
#include "../VAO.h"
#include "../VBO.h"
#include "../EBO.h"
#include "../Utils/myCube.h"

class SimpleBuilding {
private:
	VAO vao;

public:
	SimpleBuilding();
	~SimpleBuilding();

	void draw(ShaderProgram& shader);
	VAO* getVao();
};

#endif