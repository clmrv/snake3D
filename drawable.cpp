#include "drawable.hpp"

Drawable::Drawable(const char* filename) {
    tinyobj::attrib_t attrib;
    vector<tinyobj::shape_t> shapes;
    vector<tinyobj::material_t> materials;
    std::string warn;
    std::string err;


    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename);

    auto indices = &shapes[0].mesh.indices;

    glGenBuffers(1, &vertexBuffer);

    count = shapes[0].mesh.indices.size();

    vector<tinyobj::real_t> vertices;
    vector<tinyobj::real_t> normals;
    vector<tinyobj::real_t> texcoords;

    for(int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t idx = shapes[0].mesh.indices[i];
        vertices.push_back(attrib.vertices[3*idx.vertex_index+0]);
        vertices.push_back(attrib.vertices[3*idx.vertex_index+1]);
        vertices.push_back(attrib.vertices[3*idx.vertex_index+2]);

        normals.push_back(attrib.normals[3*idx.normal_index+0]);
        normals.push_back(attrib.normals[3*idx.normal_index+1]);
        normals.push_back(attrib.normals[3*idx.normal_index+2]);

        texcoords.push_back(attrib.texcoords[2*idx.texcoord_index+0]);
        texcoords.push_back(attrib.texcoords[2*idx.texcoord_index+1]);
    }

    vSize = vertices.size() * sizeof(tinyobj::real_t);
    nSize = normals.size() * sizeof(tinyobj::real_t);
    tSize = texcoords.size() * sizeof(tinyobj::real_t);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vSize + nSize + tSize, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vSize, nSize, &normals[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vSize + nSize, tSize, &texcoords[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Drawable::~Drawable() {
    if(hasTexture) {
        glDeleteTextures(1, &texName);
    }
}

void Drawable::draw(ShaderProgram *sp) {
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glEnableVertexAttribArray(sp->a("vertex"));
    glEnableVertexAttribArray(sp->a("normal"));
    if(hasTexture) {
        glEnableVertexAttribArray(sp->a("texCoord"));
    }

    // Draw
    glVertexAttribPointer(sp->a("vertex"), 3, GL_FLOAT, false, 0, (void*)0);
    glVertexAttribPointer(sp->a("normal"), 3, GL_FLOAT, false, 0, (void*)vSize);
    if(hasTexture) {
        glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, (void*)(vSize + nSize));
        glUniform1i(sp->u("textureMap"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texName);
    }

    glDrawArrays(GL_TRIANGLES, 0, count);

    glDisableVertexAttribArray(sp->a("vertex"));
    glDisableVertexAttribArray(sp->a("normal"));
    if(hasTexture) {
        glDisableVertexAttribArray(sp->a("texCoord"));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


void Drawable::loadTexture(const char* filename) {
    glActiveTexture(GL_TEXTURE0);

    vector<unsigned char> image;
    unsigned width, height;

    unsigned error = lodepng::decode(image, width, height, filename);

    if(error) { return; }

    //Import do pamięci karty graficznej
    glGenTextures(1, &texName); //Zainicjuj jeden uchwyt
    glBindTexture(GL_TEXTURE_2D, texName); //Uaktywnij uchwyt

    //Wczytaj obrazek do pamięci KG skojarzonej z uchwytem
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());  
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    hasTexture = true;
}