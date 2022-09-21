#include "Terrain.h"

Terrain::Terrain(ShaderProgram& shader) {
    terrainGenerator(shader);
}

Terrain::~Terrain() {
}

void Terrain::terrainGenerator(ShaderProgram& shader) {
	std::vector<Vertex>vertices;
	std::vector<GLuint>indices;
    std::vector<Textures>textures;

	stbi_set_flip_vertically_on_load(true);
	int width, height, bytePerPixel;
	unsigned char* data = stbi_load("resources/heightmap/heightmap.png", &width, &height, &bytePerPixel, 0);
    this->width = width;
    this->height = height;
    this->NUM_STRIPS = height - 1;
    this->TRAINGL_IN_STRIP = width * 2 - 2;

    this->startHeight = -height / 2.0f;
    this->startWidth = -width / 2.0f;



    std::cout << "Szerokosc i wysokosc: " << width << " " << height << ". Ilosc paskow i trojkatow w pasku:" << NUM_STRIPS << " " << TRAINGL_IN_STRIP;
    float yScale = 32.0f / 256.0f, yShift = 8.0f;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Vertex vertex;
            unsigned char* pixelOffset = data + (j + width * i) * bytePerPixel;
            unsigned char y = pixelOffset[0];

            glm::vec3 vectorPos;
            vectorPos.x = -height / 2.0f + i;   
            vectorPos.y = (int)y * yScale - yShift;   //mamy przedzial <-8.0f; 24.0f>
            vectorPos.z = -width / 2.0f + j;   

            vertex.pos = vectorPos;

            ///normal.x
            ///normal.y
            ///normal.z
            
            glm::vec2 vectorTex;
            vectorTex.x = i * 0.25f;
            vectorTex.y = j * 0.25f;

            vertex.texCoord = vectorTex;

            vertices.push_back(vertex);
        }
    }

    for (int i = 0; i < NUM_STRIPS; i++) {
        for (int j = 0; j < width; j++) {
            indices.push_back(j + width * i);
            indices.push_back(j + width * (i + 1));
        }
    }
    
    Textures marbleTexture = Textures("resources/terrain/white_marble.jpg", GL_TEXTURE_2D, 0, GL_RGB, "0");
    Textures grassTexture = Textures("resources/terrain/grass.jpg", GL_TEXTURE_2D, 1, GL_RGB, "1");
    /*
    marbleTexture.bind();
    marbleTexture.texUnit(shader, "texture0", 0);
    marbleTexture.unbind();
    grassTexture.bind();
    grassTexture.texUnit(shader, "texture1", 1);
    grassTexture.unbind();
    */
    textures.push_back(marbleTexture);
    textures.push_back(grassTexture);

    
    mesh.reset(new Mesh(vertices, indices, textures));
    vao.reset(mesh->getVao());
}

void Terrain::terrainRender(ShaderProgram& shader, glm::vec3& playerPos, float zFar) {
    glm::vec2 A = glm::vec2(-width / 2.0f, -height / 2.0f);
    glm::vec2 B = glm::vec2(width / 2.0f, -height / 2.0f);
    glm::vec2 C = glm::vec2(width / 2.0f, height / 2.0f);

    int start = positionToStrip(playerPos.x - zFar - 1.0f);
    int end = positionToStrip(playerPos.x + zFar + 1.0f);


    if (start < 0) start = 0;
    if (end > height - 1) end = height - 1;

    for (int i = 0; i < mesh->getTexture().size(); i++) {
        Textures texture = mesh->getTexture().at(i);
        if (i == 0) {
            texture.texUnit(shader, "texture0", 0);
        }
        if (i == 1) {
            texture.texUnit(shader, "texture1", 1);
        }
    }

    glActiveTexture(0);

    vao->bind();

    for (unsigned int strip = start; strip < end; strip++)
    {
        glDrawElements(GL_TRIANGLE_STRIP,   
            width* 2,
            GL_UNSIGNED_INT,     
            (void*)(sizeof(unsigned) * (width * 2) * strip)); 
    }
    vao->unbind();

    for (int i = 0; i < mesh->getTexture().size(); i++) {
        Textures texture = mesh->getTexture().at(i);
        texture.unbind();
    }

}

int Terrain::positionToStrip(float x) {
    int ret = x + height / 2;
    return ret;
}
