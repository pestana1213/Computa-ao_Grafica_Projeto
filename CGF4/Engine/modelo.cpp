
#include "headers/modelo.h"

using namespace std;

Modelo::Modelo() {
    r = 0.0f;
    g = 0.0f;
    b = 1.0f;

}

Modelo::Modelo(vector<float> pontos1, float r1, float g1, float b1) {
    pontos = pontos1;
    r = r1;
    g = g1;
    b = b1;
}

vector<float> Modelo::getPontos() {
    return pontos;
}


void Modelo::setTexturasPath(string path) {
    if (path != "")
        Modelo::loadTextura("C:\\Users\\Pestana\\Desktop\\CGF3\\Texturas\\" + path);
}

float Modelo::getR() {
    return r;
}

float Modelo::getG() {
    return g;
}

float Modelo::getB() {
    return b;
}


void Modelo::setPontos(vector<float> pontos1) {

    pontos = pontos1;
    pontos1.clear();
}

void Modelo::setR(float r1) {
    r = r1;
}

void Modelo::setG(float g1) {
    g = g1;
}

void Modelo::setB(float b1) {
    b = b1;
}


void Modelo::loadTextura(string path) {
    unsigned int t, tw, th;
    unsigned char* texData;
    unsigned int texID;

    //Carrega a textura para o modelo
    ilInit();
    ilEnable(IL_ORIGIN_SET);
    ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
    ilGenImages(1, &t);
    ilBindImage(t);
    ilLoadImage((ILstring)path.c_str());
    tw = ilGetInteger(IL_IMAGE_WIDTH);
    th = ilGetInteger(IL_IMAGE_HEIGHT);
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    texData = ilGetData();

    glGenTextures(1, &texID);

    glBindTexture(GL_TEXTURE_2D, texID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        tw,
        th,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        texData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    texture = texID;
}




void Modelo::prepareData() {


    glGenBuffers(1, &vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * texturas.size(), texturas.data(), GL_STATIC_DRAW);

}

void Modelo::draw() {

    glewInit();


    glBindTexture(GL_TEXTURE_2D, texture);


    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexPointer(3, GL_FLOAT, 0, 0);


    glDrawArrays(GL_TRIANGLES, 0, pontos.size() / 3);

    glBindTexture(GL_TEXTURE_2D, 0);

}


