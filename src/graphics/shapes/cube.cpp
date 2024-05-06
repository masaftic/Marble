#include "cube.h"

Cube::Cube(glm::vec3 position, glm::vec3 size)
{
	this->position = position;
	this->size = size;
}

Cube::Cube(const Cube& other)
{
    this->position = other.position;
    this->size = other.size;
}

VAO* Cube::vao = nullptr;




void Cube::initRender()
{
    Cube::vao = new VAO();

    float vertices[] = {
        //    vertices         ---tex ---    ---- normals ----
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
                                             
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
                                             
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   -1.0f,  0.0f,  0.0f,
                                             
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
                                             
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
                                             
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f,   0.0f,  1.0f,  0.0f
    };

    VBO vbo(vertices, sizeof(vertices));

    vao->Bind();

    vao->LinkAtrrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao->LinkAtrrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao->LinkAtrrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(5 * sizeof(float)));

    vbo.Unbind();
    vao->Unbind();
}


void Cube::Draw(Cube& cube, Shader& shader, Texture& texture)
{
    shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, cube.position);
    model = glm::rotate(model, cube.rotate, cube.rotationAxis);
    model = glm::scale(model, cube.size);

    shader.setMat4("model", model);
    shader.setVec3("color", cube.color);


    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    vao->Bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


