#include "headers/ponto.h"
#include "headers/modelo.h"
#include <vector>

using namespace std;

    Modelo::Modelo(){
    }

    Modelo::Modelo(list<Ponto> pontosLista1) {
        pontosLista = pontosLista1;
    }

    list<Ponto> Modelo::getPontos() {
        return pontosLista;
    }

    void Modelo::setPontos(list<Ponto> pontosLista1) {
        pontosLista = pontosLista1;
    }



