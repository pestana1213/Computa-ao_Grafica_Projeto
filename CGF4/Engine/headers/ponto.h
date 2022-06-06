#ifndef CLASS2_PONTO_H
#define CLASS2_PONTO_H

//classe ponto que contem as coordenadas x,y,z de cada ponto junto com os getters e setters
class Ponto {
    float x;
    float y;
    float z;

public:

    Ponto();
    Ponto(float a, float b, float c);

    float getX();

    float getY();

    float getZ();

    void setX(float a);

    void setY(float b);

    void setZ(float c);
};


#endif //CLASS2_PONTO_H
