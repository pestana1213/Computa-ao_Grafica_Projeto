#include "headers/transformacoes.h"

Rotacao::Rotacao() {
    x = 0;
    y = 0;
    z = 0;
    tempo = 0;
    angulo = 0;
}

Rotacao::Rotacao(float x1, float y1, float z1, float t, float angulo1) {
    x = x1;
    y = y1;
    z = z1;
    tempo = t;
    angulo = angulo1;
}


float Rotacao::getAngulo() {
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

float Rotacao::getTempo() {
    return tempo;
}

void Rotacao::setAngulo(float angulo1) {
    angulo = angulo1;
}

void Rotacao::setTempo(float t) {
    tempo = t;
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


Translacao::Translacao() {
    x = 0;
    y = 0;
    z = 0;
}

Translacao::Translacao(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
}

Translacao::Translacao(float t, vector<Ponto> v) {
    tempo = t;
    pontos = v;
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

float Translacao::getTempo() {
    return tempo;
}

vector<Ponto> Translacao::getPontos() {
    return pontos;
}

vector<Ponto> Translacao::getCurva() {
    return pontosCurva;
}

void Translacao::setTempo(float t) {
    tempo = t;
}

void Translacao::setPontos(vector<Ponto> p) {
    pontos = p;
}

void Translacao::setCurva(vector<Ponto> p) {
    pontosCurva = p;
}


void Translacao::buildRotMatrix(float* x, float* y, float* z, float* m) {

    m[0] = x[0]; m[1] = x[1]; m[2] = x[2]; m[3] = 0;
    m[4] = y[0]; m[5] = y[1]; m[6] = y[2]; m[7] = 0;
    m[8] = z[0]; m[9] = z[1]; m[10] = z[2]; m[11] = 0;
    m[12] = 0; m[13] = 0; m[14] = 0; m[15] = 1;
}


void Translacao::cross(float* a, float* b, float* res) {

    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}


void Translacao::normalize(float* a) {

    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    a[0] = a[0] / l;
    a[1] = a[1] / l;
    a[2] = a[2] / l;
}

void Translacao::getCatmullRomPoint(float t, Ponto p0, Ponto p1, Ponto p2, Ponto p3, float* pos, float* deriv) {

    float M[4][4] = { {-0.5f,  1.5f, -1.5f,  0.5f},
                    { 1.0f, -2.5f,  2.0f, -0.5f},
                    {-0.5f,  0.0f,  0.5f,  0.0f},
                    { 0.0f,  1.0f,  0.0f,  0.0f} };

    float P[4][3] = { {p0.getX(),p0.getY(), p0.getZ()},
                    {p1.getX(), p1.getY(), p1.getZ()},
                    {p2.getX(), p2.getY(), p2.getZ()},
                    {p3.getX(), p3.getY(), p3.getZ()} };

    // A = M * P

    float A[4][3] = { 0 };

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 4; k++) A[i][j] += M[i][k] * P[k][j];

    float T[4] = { t * t * t, t * t, t, 1 };

    // pos = T * A

    pos[0] = 0;
    pos[1] = 0;
    pos[2] = 0;

    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 4; k++) pos[j] += T[k] * A[k][j];

    deriv[0] = 0;
    deriv[1] = 0;
    deriv[2] = 0;

    float Tderiv[4] = { 3 * t * t, 2 * t, 1, 0 };

    for (int j = 0; j < 3; j++)
        for (int k = 0; k < 4; k++) deriv[j] += Tderiv[k] * A[k][j];

}


void Translacao::getGlobalCatmullRomPoint(float gt, float* pos, float* deriv, vector<Ponto> pontos) {

    int tamLoop = pontos.size(); // Points that make up the loop for catmull-rom interpolation
    float t = gt * tamLoop; // this is the real global t
    int index = floor(t);  // which segment
    t = t - index; // where within  the segment

    // indices store the points
    int indices[4];
    indices[0] = (index + tamLoop - 1) % tamLoop;
    indices[1] = (indices[0] + 1) % tamLoop;
    indices[2] = (indices[1] + 1) % tamLoop;
    indices[3] = (indices[2] + 1) % tamLoop;

    getCatmullRomPoint(t, pontos[indices[0]], pontos[indices[1]], pontos[indices[2]], pontos[indices[3]], pos, deriv);
}

void Translacao::buildCurve(float* pos, float* deriv) {

    for (float t = 0; t < 1; t += 0.001) {

        getGlobalCatmullRomPoint(t, pos, deriv, pontos);
        pontosCurva.push_back(*new Ponto(pos[0], pos[1], pos[2]));
    }

}

void Translacao::drawCatmullRomCurve() {

    int tam = pontosCurva.size();

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < tam; i++) {
        Ponto p = pontosCurva[i];
        glVertex3f(p.getX(), p.getY(), p.getZ());
    }

    glEnd();
}

void Translacao::alinhamentoCurva(float* deriv) {

    float Z[3];
    float Y[3] = { 0,1,0 };
    float X[3] = { deriv[0],deriv[1],deriv[2] };
    float m[16];

    cross(X, Y, Z);
    cross(Z, X, Y);

    normalize(X);
    normalize(Y);
    normalize(Z);

    buildRotMatrix(X, Y, Z, m);

    glMultMatrixf((float*)m);
}

void Translacao::draw() {
    float pos[3];
    float deriv[3];
    float te, gt;
    if (tempo != 0 && pontos.size() > 3) {
        te = glutGet(GLUT_ELAPSED_TIME) % (int)(tempo * 1000);
        gt = te / (tempo * 1000);
        buildCurve(pos, deriv);
        drawCatmullRomCurve();
        getGlobalCatmullRomPoint(gt, pos, deriv, pontos);
        pontosCurva.clear();
        glTranslatef(pos[0], pos[1], pos[2]);
        alinhamentoCurva(deriv);
    }
}

//ESCALA

Escala::Escala() {
    x = 1;
    y = 1;
    z = 1;
}

Escala::Escala(float x1, float y1, float z1) {
    x = x1;
    y = y1;
    z = z1;
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
