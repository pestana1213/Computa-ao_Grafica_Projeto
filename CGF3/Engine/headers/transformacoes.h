
#ifndef CLASS2_TRANSFORMACOES_H
#define CLASS2_TRANSFORMACOES_H

#include "ponto.h"
#include <vector>
#include <GL/glut.h>

using namespace std;

//ROTAÇÃO

class Rotacao {
    float tempo;
    float x;
    float y;
    float z;
    float angulo;
public:

    Rotacao();

    Rotacao(float, float, float, float, float);

    float getTempo();

    float getAngulo();

    float getX();

    float getY();

    float getZ();

    void setAngulo(float);

    void setTempo(float);

    void setX(float);

    void setY(float);

    void setZ(float);

};

//TRANSLAÇÃO

class Translacao {
    float x;
    float y;
    float z;
    float tempo;
    vector <Ponto> pontos;
    vector <Ponto> pontosCurva;

public:

    Translacao();

    Translacao(float, float, float);

    Translacao(float, vector<Ponto>);

    float getX();

    float getY();

    float getZ();

    void setX(float);

    void setY(float);

    void setZ(float);

    float getTempo();

    vector<Ponto> getPontos();

    vector<Ponto> getCurva();

    void setTempo(float);

    void setPontos(vector<Ponto>);

    void setCurva(vector<Ponto>);

    void buildRotMatrix(float*, float*, float*, float*);

    void cross(float*, float*, float*);

    void normalize(float*);

    void getCatmullRomPoint(float, Ponto, Ponto, Ponto, Ponto, float*, float*);

    void getGlobalCatmullRomPoint(float, float*, float*, vector<Ponto>);

    void buildCurve(float*, float*);

    void alinhamentoCurva(float*);

    void drawCatmullRomCurve();

    void draw();

};

//ESCALA

class Escala {
    float x;
    float y;
    float z;

public:

    Escala();

    Escala(float, float, float);

    float getX();

    float getY();

    float getZ();

    void setX(float);

    void setY(float);

    void setZ(float);

};

#endif //CLASS2_TRANSFORMACOES_H
