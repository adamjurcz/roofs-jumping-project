#ifndef SIMPLEBUILDING_H
#define SIMPLEBUILDING_H

#include "ShaderProgram.h"
#include "Textures.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

#include "myCube.h"

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