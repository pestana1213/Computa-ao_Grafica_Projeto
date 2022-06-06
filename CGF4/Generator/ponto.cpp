
#include "headers/ponto.h"

//classe ponto que contem as coordenadas x,y,z de cada ponto junto com os getters e setters

    Ponto::Ponto() {
        x = 0;
        y = 0;
        z = 0;
    }

    Ponto::Ponto(float a, float b, float c) {
        x = a;
        y = b;
        z = c;
    }

    float Ponto:: getX() {
        return x;
    }

    float Ponto:: getY() {
        return y;
    }

    float Ponto:: getZ() {
        return z;
    }

    void Ponto:: setX(float a) {
        x = a;
    }

    void Ponto:: setY(float b) {
        y = b;
    }

    void Ponto:: setZ(float c) {
        z = c;
    }
