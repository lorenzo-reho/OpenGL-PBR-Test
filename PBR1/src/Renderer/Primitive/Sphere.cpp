#include "Sphere.h"

Sphere::Sphere(glm::mat4 transform) : X_SEGMENTS(64), Y_SEGMENTS(64), radius(1.0f), Object(transform){
    CreateObject();
}

Sphere::Sphere(glm::mat4 transform, int segments, float radius): Object(transform){
    this->X_SEGMENTS = segments;
    this->Y_SEGMENTS = segments;
    this->radius = radius;

    CreateObject();
}

void Sphere::Render(Shader* shader) {
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, (void*)0);
    glBindVertexArray(0);
}

void Sphere::CreateObject(){
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> textCoord;

    std::vector<unsigned int> indices;
    std::vector<float> data;


    for (int ys = 0; ys <= Y_SEGMENTS; ys++) {
        float yratio = (float)ys / Y_SEGMENTS;

        float phi = PI/2 - PI * yratio; // -90 a 90 gradi

        for (int xs = 0; xs <= X_SEGMENTS; xs++) {
            float xratio = (float)xs / X_SEGMENTS;

            float theta = 2 * PI * xratio; // 0 a 360 gradi

            float x = radius * cos(phi) * sin(theta);
            float y = radius * sin(phi);
            float z = radius * cos(phi) * cos(theta);

            float nx = x/radius;
            float ny = y/radius;
            float nz = z/radius;

            float u = xratio;
            float v = yratio;

            positions.push_back(glm::vec3(x, y, z));
            normals.push_back(glm::vec3(nx, ny, nz));
            textCoord.push_back(glm::vec2(u, v));

        }
    }

    for (int ys = 0; ys < Y_SEGMENTS; ++ys) {

        int k1 = ys * (X_SEGMENTS + 1);
        int k2 = k1 + X_SEGMENTS + 1;

        for (int xs = 0; xs < X_SEGMENTS; xs++) {

            if(ys != 0){
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1+1);
            }

            if (ys != (Y_SEGMENTS-1)) {
                indices.push_back(k1+1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }

            k1++;
            k2++;

        }
    }

    indexCount = static_cast<unsigned int>(indices.size());

    for (int i = 0; i < positions.size(); i++) {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);

        data.push_back(normals[i].x);
        data.push_back(normals[i].y);
        data.push_back(normals[i].z);

        data.push_back(textCoord[i].x);
        data.push_back(textCoord[i].y);
    }

    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);


    glBindVertexArray(_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    unsigned int stride = 8 * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}