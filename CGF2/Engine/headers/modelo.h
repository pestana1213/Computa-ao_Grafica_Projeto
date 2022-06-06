#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>

using namespace std;

class Modelo {
    list<Ponto> pontosLista;

    public:

        Modelo();

        Modelo(list<Ponto> pontosLista1);

        list<Ponto> getPontos();

        void setPontos(list<Ponto> pontosLista);

    };


