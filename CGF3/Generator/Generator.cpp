#include "headers\ponto.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h> 
#include <stdio.h>
using namespace std;
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

string fileName;


//converte para string as coordenadas x,y,z é uma linha no ficheiro .3d
string converte(float x, float y, float z) {

    return to_string(x) + " " + to_string(y) + " " + to_string(z);

}


void drawPlano(int len, int div) {

    fstream(file);
    file.open("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\3dFiles\\" + fileName, fstream::out); //abre ficheiro para escrita
    if (file.is_open()) {

        float lenAux = (float)len / div;
        int vertices = 2 * div * div * 3;
        file << to_string(vertices) << endl;

        for (int i = 0; i < div; i++) {
            for (int j = 0; j < div; j++) {

                file << converte(-len + (i * lenAux) + lenAux, 0.0f, len - (j * lenAux) - lenAux) << endl;
                file << converte(-len + (i * lenAux), 0.0f, len - (j * lenAux) - lenAux) << endl;
                file << converte(-len + (i * lenAux), 0.0f, len - (j * lenAux)) << endl;

                file << converte(-len + (i * lenAux) + lenAux, 0.0f, len - (j * lenAux)) << endl;
                file << converte(-len + (i * lenAux) + lenAux, 0.0f, len - (j * lenAux) - lenAux) << endl;
                file << converte(-len + (i * lenAux), 0.0f, len - (j * lenAux)) << endl;


            }
        }
        file.close();

    }
    else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}

void drawBox(int units, int div) {
    float x = float(units);float y = float(units);float z = float(units);

    float pX = (float)units / div;
    float pY = (float)units / div;
    float pZ = (float)units / div;

    x = x / 2;
    z = z / 2;

    fstream(file);
    file.open("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\3dFiles\\" + fileName, fstream::out); //abre ficheiro para escrita

    if (file.is_open()) {
        int vertices = 6 * 2 * div * div * 3;
        file << to_string(vertices) << endl;

        for (int i = 0; i < div; i++) {
            for (int j = 0; j < div; j++) {

                //base
                file << converte(-x + (i * pX), 0.0f, z - (j * pZ)) << endl;
                file << converte(-x + (i * pX), 0.0f, z - (j * pZ) - pZ) << endl;
                file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ) - pZ) << endl;

                file << converte(-x + (i * pX), 0.0f, z - (j * pZ)) << endl;
                file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ) - pZ) << endl;
                file << converte(-x + (i * pX) + pX, 0.0f, z - (j * pZ)) << endl;

                //face cima
                file << converte(-x + (i * pX), y, -z + (j * pZ)) << endl;
                file << converte(-x + (i * pX), y, -z + (j * pZ) + pZ) << endl;
                file << converte(-x + (i * pX) + pX, y, -z + (j * pZ) + pZ) << endl;

                file << converte(-x + (i * pX), y, -z + (j * pZ)) << endl;
                file << converte(-x + (i * pX) + pX, y, -z + (j * pZ) + pZ) << endl;
                file << converte(-x + (i * pX) + pX, y, -z + (j * pZ)) << endl;

                //face trÃ¡s
                file << converte(-x + (i * pX) + pX, j * pY, -z) << endl;
                file << converte(-x + (i * pX), j * pY, -z) << endl;
                file << converte(-x + (i * pX) + pX, (j * pY) + pY, -z) << endl;

                file << converte(-x + (i * pX), j * pY, -z) << endl;
                file << converte(-x + (i * pX), (j * pY) + pY, -z) << endl;
                file << converte(-x + (i * pX) + pX, j * pY + pY, -z) << endl;

                //face frontal
                file << converte(-x + (i * pX), y - (j * pY), z) << endl;
                file << converte(-x + (i * pX), y - (j * pY) - pY, z) << endl;
                file << converte(-x + (i * pX) + pX, y - (j * pY) - pY, z) << endl;

                file << converte(-x + (i * pX), y - (j * pY), z) << endl;
                file << converte(-x + (i * pX) + pX, y - (j * pY) - pY, z) << endl;
                file << converte(-x + (i * pX) + pX, y - (j * pY), z) << endl;

                //face esquerda
                file << converte(-x, y - (i * pY), -z + (j * pZ)) << endl;
                file << converte(-x, y - (i * pY) - pY, -z + (j * pZ)) << endl;
                file << converte(-x, y - (i * pY) - pY, -z + (j * pZ) + pZ) << endl;

                file << converte(-x, y - (i * pY), -z + (j * pZ)) << endl;
                file << converte(-x, y - (i * pY) - pY, -z + (j * pZ) + pZ) << endl;
                file << converte(-x, y - (i * pY), -z + (j * pZ) + pZ) << endl;

                //face direita

                file << converte(x, y - (i * pY), z - (j * pZ)) << endl;
                file << converte(x, y - (i * pY) - pY, z - (j * pZ)) << endl;
                file << converte(x, y - (i * pY) - pY, z - (j * pZ) - pZ) << endl;

                file << converte(x, y - (i * pY), z - (j * pZ)) << endl;
                file << converte(x, y - (i * pY) - pY, z - (j * pZ) - pZ) << endl;
                file << converte(x, y - (i * pY), z - (j * pZ) - pZ) << endl;

            }
        }

        file.close();
    }
    else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}



//escreve os pontos do cone no ficheiro
void drawCone(float radius, float height, float slices, float stacks) {

    float angulo = (float)2 * M_PI / slices;
    float alturaStack = height / stacks;
    float alpha2;
    float alpha1;
    float alturaCima;
    float alturaBaixo;
    float raio2 = radius;
    float raio2ant;
    float angulo2;

    fstream(file);
    file.open("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\3dFiles\\" + fileName, fstream::out); //abre ficheiro para escrita
    if (file.is_open()) {
        int vertices = (slices * 3) + slices * (3 + 6 * (stacks - 1));
        file << to_string(vertices) << endl;

        for (int j = 1; j <= stacks; j++) {

            alturaCima = alturaStack * j;
            raio2 = raio2 - (radius / stacks);

            for (int i = 1; i <= slices; i++) {

                alpha1 = angulo * i;
                alpha2 = alpha1 + angulo;

                // stack 1
                if (j == 1) {


                    //base

                    file << converte(0.0f, 0.0f, 0.0f) << endl;
                    file << converte(radius * sin(alpha2), 0, radius * cos(alpha2)) << endl;
                    file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;


                    // lados

                    file << converte(radius * sin(alpha2), 0, radius * cos(alpha2)) << endl;
                    file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
                    file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;


                    file << converte(radius * sin(alpha1), 0, radius * cos(alpha1)) << endl;
                    file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
                    file << converte(raio2 * sin(alpha1), alturaCima, raio2 * cos(alpha1)) << endl;



                }

                else if (j != stacks) {


                    file << converte(raio2ant * sin(alpha2), alturaBaixo, raio2ant * cos(alpha2)) << endl;
                    file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
                    file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;


                    file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;
                    file << converte(raio2 * sin(alpha2), alturaCima, raio2 * cos(alpha2)) << endl;
                    file << converte(raio2 * sin(alpha1), alturaCima, raio2 * cos(alpha1)) << endl;

                }


                else {

                    file << converte(raio2ant * sin(alpha2), alturaBaixo, raio2ant * cos(alpha2)) << endl;
                    file << converte(0, alturaCima, 0) << endl;
                    file << converte(raio2ant * sin(alpha1), alturaBaixo, raio2ant * cos(alpha1)) << endl;

                }

            }

            alturaBaixo = alturaCima;
            raio2ant = raio2;
        }

        file.close();
    }
    else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }

}


//escreve os pontos da esfera no ficheiro
void drawSphere(float radius, int slices, int stacks) {


    float alfa = (2 * M_PI) / slices;//fatias
    float beta = M_PI / stacks;//camadas

    fstream(file);
    file.open("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\3dFiles\\" + fileName, fstream::out);  //abre ficheiro para escrita
    if (file.is_open()) {

        int vertices = slices * (2 + 2 * (stacks - 2)) * 3;
        file << to_string(vertices) << endl;

        for (int i = 0; i < slices; i++) {
            float alfa1 = alfa * i;
            //cima


            file << converte(radius * cos(M_PI / 2) * sin(alfa1), radius * sin(M_PI / 2), radius * cos(M_PI / 2) * cos(alfa1)) << endl;
            file << converte(radius * cos(M_PI / 2 - beta) * sin(alfa1), radius * sin(M_PI / 2 - beta), radius * cos(M_PI / 2 - beta) * cos(alfa1)) << endl;
            file << converte(radius * cos(M_PI / 2 - beta) * sin(alfa1 + alfa), radius * sin(M_PI / 2 - beta), radius * cos(M_PI / 2 - beta) * cos(alfa1 + alfa)) << endl;

            //baixo


            file << converte(radius * cos(-M_PI / 2) * sin(alfa1), sin(-M_PI / 2) * radius, radius * cos(-M_PI / 2) * cos(alfa1)) << endl;
            file << converte(radius * cos((-M_PI / 2) + beta) * sin(alfa1 + alfa), radius * sin((-M_PI / 2) + beta), radius * cos((-M_PI / 2) + beta) * cos(alfa1 + alfa)) << endl;
            file << converte(radius * cos((-M_PI / 2) + beta) * sin(alfa1), radius * sin((-M_PI / 2) + beta), radius * cos((-M_PI / 2) + beta) * cos(alfa1)) << endl;


            for (int j = 1; j < stacks - 1; j++) {
                float beta1 = M_PI / 2 - (j * beta);

                file << converte(radius * cos(beta1) * sin(alfa1), radius * sin(beta1), radius * cos(beta1) * cos(alfa1)) << endl;
                file << converte(radius * cos(beta1 - beta) * sin(alfa1), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1)) << endl;
                file << converte(radius * cos(beta1) * sin(alfa1 + alfa), radius * sin(beta1), radius * cos(beta1) * cos(alfa1 + alfa)) << endl;



                file << converte(radius * cos(beta1 - beta) * sin(alfa1), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1)) << endl;
                file << converte(radius * cos(beta1 - beta) * sin(alfa1 + alfa), radius * sin(beta1 - beta), radius * cos(beta1 - beta) * cos(alfa1 + alfa)) << endl;
                file << converte(radius * cos(beta1) * sin(alfa1 + alfa), radius * sin(beta1), radius * cos(beta1) * cos(alfa1 + alfa)) << endl;

            }
        }

        file.close();
    }
    else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }


}

Ponto calcula(std::vector<int> patch, std::vector<Ponto*> pontos, float u, float v) {



    float coef1 = (1 - u) * (1 - u) * (1 - u);
    float coef2 = 3 * (1 - u) * (1 - u) * u;
    float coef3 = 3 * (1 - u) * u * u;
    float coef4 = u * u * u;

    float x1 = coef1 * pontos[patch[0]]->getX() + coef2 * pontos[patch[1]]->getX() + coef3 * pontos[patch[2]]->getX() + coef4 * pontos[patch[3]]->getX();
    float x2 = coef1 * pontos[patch[4]]->getX() + coef2 * pontos[patch[5]]->getX() + coef3 * pontos[patch[6]]->getX() + coef4 * pontos[patch[7]]->getX();
    float x3 = coef1 * pontos[patch[8]]->getX() + coef2 * pontos[patch[9]]->getX() + coef3 * pontos[patch[10]]->getX() + coef4 * pontos[patch[11]]->getX();
    float x4 = coef1 * pontos[patch[12]]->getX() + coef2 * pontos[patch[13]]->getX() + coef3 * pontos[patch[14]]->getX() + coef4 * pontos[patch[15]]->getX();

    float y1 = coef1 * pontos[patch[0]]->getY() + coef2 * pontos[patch[1]]->getY() + coef3 * pontos[patch[2]]->getY() + coef4 * pontos[patch[3]]->getY();
    float y2 = coef1 * pontos[patch[4]]->getY() + coef2 * pontos[patch[5]]->getY() + coef3 * pontos[patch[6]]->getY() + coef4 * pontos[patch[7]]->getY();
    float y3 = coef1 * pontos[patch[8]]->getY() + coef2 * pontos[patch[9]]->getY() + coef3 * pontos[patch[10]]->getY() + coef4 * pontos[patch[11]]->getY();
    float y4 = coef1 * pontos[patch[12]]->getY() + coef2 * pontos[patch[13]]->getY() + coef3 * pontos[patch[14]]->getY() + coef4 * pontos[patch[15]]->getY();

    float z1 = coef1 * pontos[patch[0]]->getZ() + coef2 * pontos[patch[1]]->getZ() + coef3 * pontos[patch[2]]->getZ() + coef4 * pontos[patch[3]]->getZ();
    float z2 = coef1 * pontos[patch[4]]->getZ() + coef2 * pontos[patch[5]]->getZ() + coef3 * pontos[patch[6]]->getZ() + coef4 * pontos[patch[7]]->getZ();
    float z3 = coef1 * pontos[patch[8]]->getZ() + coef2 * pontos[patch[9]]->getZ() + coef3 * pontos[patch[10]]->getZ() + coef4 * pontos[patch[11]]->getZ();
    float z4 = coef1 * pontos[patch[12]]->getZ() + coef2 * pontos[patch[13]]->getZ() + coef3 * pontos[patch[14]]->getZ() + coef4 * pontos[patch[15]]->getZ();

    float Coef1 = (1 - v) * (1 - v) * (1 - v);
    float Coef2 = 3 * (1 - v) * (1 - v) * v;
    float Coef3 = 3 * (1 - v) * v * v;
    float Coef4 = v * v * v;

    float x = Coef1 * x1 + Coef2 * x2 + Coef3 * x3 + Coef4 * x4;
    float y = Coef1 * y1 + Coef2 * y2 + Coef3 * y3 + Coef4 * y4;
    float z = Coef1 * z1 + Coef2 * z2 + Coef3 * z3 + Coef4 * z4;

    return Ponto(x, y, z);

}


void curvaBezier(std::vector<Ponto>* vertices, std::vector<int> patch, std::vector<Ponto*> pontosControlo, float u, float v, float intervalo) {

    Ponto p1 = calcula(patch, pontosControlo, u, v);
    Ponto p2 = calcula(patch, pontosControlo, u, v + intervalo);
    Ponto p3 = calcula(patch, pontosControlo, u + intervalo, v);
    Ponto p4 = calcula(patch, pontosControlo, u + intervalo, v + intervalo);

    vertices->push_back(p1);
    vertices->push_back(p4);
    vertices->push_back(p2);

    vertices->push_back(p4);
    vertices->push_back(p1);
    vertices->push_back(p3);
}

void drawBezierPatches(int nivel, string origem) {
    float intervalo = (float)1.0 / nivel;
    string linha;
    std::vector<std::vector<int>> patches;
    std::vector<Ponto*> pontosControlo;
    std::vector<Ponto> resultado;

    //abrir o ficheiro
    ifstream file1("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\Patches\\" + origem + ".patch");
    if (!file1.is_open()) { cout << "Erro ao ler o ficheiro paches" << endl; return; }
    //pega na primeira linha que é o número de patches ou seja numero de linhas a ler 
    getline(file1, linha);
    int nPatches = atoi(linha.c_str());

    int t;
    for (int i = 0; i < nPatches; i++) {
        getline(file1, linha);     //pegar na linha atual
        stringstream strstream(linha);
        patches.push_back(std::vector<int>());
        while (strstream >> t) {	// retirar as ,
            patches[i].push_back(t);
            if (strstream.peek() == ',') {
                strstream.ignore();
            }
        }
    }
    //pega na primeira linha que é o número de vértices ou seja numero de linhas a ler (1 vertice por linha)
    getline(file1, linha);
    int nLinhas = atoi(linha.c_str());
    float x, y, z;
    for (int i = 0; i < nLinhas; i++) {
        getline(file1, linha);     //pegar na linha atual
        stringstream strstream(linha);
        strstream >> x;

        if (strstream.peek() == ',') {
            strstream.ignore();
        }

        strstream >> y;
        if (strstream.peek() == ',') {
            strstream.ignore();
        }

        strstream >> z;
        if (strstream.peek() == ',') {
            strstream.ignore();
        }

        pontosControlo.push_back(new Ponto(x, y, z)); //adiciona o Ponto lido á lista de pontos
    }
    file1.close();

    for (int i = 0; i < nPatches; i++) {
        float u = 0.0;
        float v = 0.0;
        for (int j = 0; j < nivel; j++) {
            for (int m = 0; m < nivel; m++) {
                curvaBezier(&resultado, patches[i], pontosControlo, u, v, intervalo);
                v += intervalo;
            }
            u += intervalo;
            v = 0.0;
        }
    }
    fstream(file);
    file.open("C:\\Users\\Pestana\\Desktop\\Trabalho_Fase_3_Grupo10\\3dFiles\\" + fileName, fstream::out);  //abre ficheiro para escrita
    if (file.is_open()) {
        int vertices = resultado.size();
        file << to_string(vertices) << endl;
        for (int i = 0; i < vertices; i++) {
            file << converte(resultado[i].getX(), resultado[i].getY(), resultado[i].getZ()) << endl;
        }
        file.close();
    }
    else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}

//na main comparamos sempre o primeiro argumento com as várias formas possiveis de gerar
int  main(int argc, char* argv[]) {


    if (strcmp(argv[1], "plane") == 0 && argc == 5) {
        int dimensao = atoi(argv[2]);
        int divisao = atoi(argv[3]);
        fileName = argv[4];
        drawPlano(dimensao, divisao);
        return 0;
    }


    if (strcmp(argv[1], "box") == 0 && argc == 5) {
        int unidades = atoi(argv[2]);
        int divisao = atoi(argv[3]);
        fileName = argv[4];
        drawBox(unidades, divisao);

        return 0;
    }



    if (strcmp(argv[1], "cone") == 0 && argc == 7) {
        float radius = stof(argv[2]);
        float height = stof(argv[3]);
        int slices = atoi(argv[4]);
        int stack = atoi(argv[5]);
        fileName = argv[6];

        drawCone(radius, height, slices, stack);
        return 0;
    }


    if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
        float radius = stof(argv[2]);
        int slices = atoi(argv[3]);
        int stack = atoi(argv[4]);
        fileName = argv[5];

        drawSphere(radius, slices, stack);
        return 0;
    }

    if (strcmp(argv[1], "bezier") == 0 && argc == 5) {
        int nivel = atoi(argv[3]);
        string origem = argv[2];
        fileName = argv[4];

        drawBezierPatches(nivel, origem);
        return 0;
    }



    else {
        cout << "Argumentos insuficientes!" << endl;
        printf("1: %s \n", argv[0]);
        printf("2: %s \n", argv[1]);
        printf("3: %s \n", argv[2]);
        printf("4: %s \n", argv[3]);
        printf("5: %s \n", argv[4]);
        printf("6: %s \n", argv[5]);
        printf("7: %s \n", argv[6]);
        printf("8: %s \n", argv[6]);

        return 0;
    }



}