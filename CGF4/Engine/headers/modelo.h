#include "teste.h"
#include <list>
#include <vector>
#include <string>
#include "ponto.h"
#include <IL/il.h>

using namespace std;

class Modelo {

    vector<float> pontos;
    GLuint vertices;
    GLuint normals;
    float r;
    float g;
    float b;
    vector<float> texturas;
    GLuint texture;


public:

    Modelo();

    Modelo(vector<float> pontos, float r, float g, float b);

    vector<float> getPontos();

    void setTexturasPath(string path);

    float getR();

    float getG();

    float getB();

    void setPontos(vector<float> pontos);

    void setR(float r);

    void setG(float g);

    void setB(float b);

    void prepareData();

    void draw();

    void loadTextura(string path);
};