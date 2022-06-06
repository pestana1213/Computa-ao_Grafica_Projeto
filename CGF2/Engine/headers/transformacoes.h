
#ifndef CLASS2_TRANSFORMACOES_H
#define CLASS2_TRANSFORMACOES_H

//ROTAÇÃO

class Rotacao{
    float angulo;
    float x;
    float y;
    float z;

public:

    Rotacao();

    Rotacao(float, float, float, float);

    float getAngulo();

    float getX();

    float getY();

    float getZ();

    void setAngulo(float);

    void setX(float);

    void setY(float);

    void setZ(float);

};

//TRANSLAÇÃO

class Translacao{
    float x;
    float y;
    float z;

public:

    Translacao();

    Translacao(float, float, float);

    float getX();

    float getY();

    float getZ();

    void setX(float);

    void setY(float);

    void setZ(float);

};

//ESCALA

class Escala{
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
