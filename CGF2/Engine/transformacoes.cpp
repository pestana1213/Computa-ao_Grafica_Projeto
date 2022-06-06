#include "headers/transformacoes.h"

        Rotacao::Rotacao(){
            angulo=0;
            x=0;
            y=0;
            z=0;
        }

        Rotacao::Rotacao(float x1, float y1, float z1, float angulo1){
            angulo=angulo1;
            x=x1;
            y=y1;
            z=z1;
        }

        float Rotacao::getAngulo(){
            return angulo;
        }

        float Rotacao::getX() {
            return x;
        }

        float Rotacao::getY() {
            return y;
        }

        float Rotacao::getZ() {
            return z;
        }

        void Rotacao::setAngulo(float angulo1){
            angulo = angulo1;
        }

        void Rotacao::setX(float a) {
            x = a;
        }

        void Rotacao::setY(float b) {
            y = b;
        }

        void Rotacao::setZ(float c) {
            z = c;
        }


//TRANSLAÇÃO


    Translacao::Translacao(){
        x=0;
        y=0;
        z=0;
    }

    Translacao::Translacao(float x1, float y1, float z1){
        x=x1;
        y=y1;
        z=z1;
    }

    float Translacao::getX() {
        return x;
    }

    float Translacao::getY() {
        return y;
    }

    float Translacao::getZ() {
        return z;
    }

    void Translacao::setX(float a) {
        x = a;
    }

    void Translacao::setY(float b) {
        y = b;
    }

    void Translacao::setZ(float c) {
        z = c;
    }


//ESCALA

    Escala::Escala(){
        x=1;
        y=1;
        z=1;
    }

    Escala::Escala(float x1, float y1, float z1){
        x=x1;
        y=y1;
        z=z1;
    }

    float Escala::getX() {
        return x;
    }

    float Escala::getY() {
        return y;
    }

    float Escala::getZ() {
        return z;
    }

    void Escala::setX(float a) {
        x = a;
    }

    void Escala::setY(float b) {
        y = b;
    }

    void Escala::setZ(float c) {
        z = c;
    }
    