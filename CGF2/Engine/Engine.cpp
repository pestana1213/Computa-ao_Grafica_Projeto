#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


#include <iostream>
#include <fstream>
#include <string>
#include <string.h> 
#include <stdio.h>
#include "tinyxml2.h"
#include "headers/grupo.h"
#include <sstream>
#include <string>
#include <algorithm> 
#include <vector>

using namespace tinyxml2;
using namespace std;

float camX , camY , camZ ;  //posicao x,y,z da camara
int alpha = 0, beta = 0, r = 20;      // angulos e raio da camara
int xInicial, yInicial, modoRato = 0;   //posicoes anteriores da camara e modo da mesma

bool eixos = true;   //eixos
int tipo = GL_LINE;   //tipo de desenho linhas, pontos ou fill
float v = 1.0f, g = 1.0f, b = 1.0f; //cores do desenho

double lookX;
double lookY;
double lookZ;
double upX;
double upY;
double upZ;
int fov;
int near;
double far;

vector<Grupo> gruposLista;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Reset the coordinate system before modifying
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective
	gluPerspective(fov, ratio, near, far);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

//funcao desenha
//pega na lista de pontos e vai percorrer a mesma usando um iterador, a cada 3 pontos desenha um triangulo
//desta forma, cada iteração do ciclo for 3 pontos e um triangulo sao desenhados avançando assim o iterador em 3 posiçoes
void drawPontos(list<Ponto> pontosLista) {

	for (auto it = pontosLista.begin(); it != pontosLista.end(); ) {
		glBegin(GL_TRIANGLES);
		glVertex3f(it->getX(), it->getY(), it->getZ());
		++it;
		glVertex3f(it->getX(), it->getY(), it->getZ());
		++it;
		glVertex3f(it->getX(), it->getY(), it->getZ());
		++it;
		glEnd();
	}

}


void drawGrupo(Grupo gR) {
	Translacao t = gR.getTranslacao();
	Rotacao r = gR.getRotacao();
	Escala e = gR.getEscala();
	string ordem = gR.getOrdem();
	vector<Grupo> filhos = gR.getFilhos();

	vector<Modelo> m = gR.getModelos();


	glPushMatrix();

	for (int i = 0; i < 5; i += 2) {
		switch (ordem[i]) {
		case 'T':
			glTranslatef(t.getX(), t.getY(), t.getZ());
			break;
		case 'R':
			glRotatef(r.getAngulo(), r.getX(), r.getY(), r.getZ());
			break;
		case 'E':
			glScalef(e.getX(), e.getY(), e.getZ());
			break;
		default:
			break;
		}
	}


	for (int i = 0; i < m.size(); i++) {
		glColor3f(v, g, b);
		drawPontos(m[i].getPontos());
	}

	for (int i = 0; i < filhos.size(); i++) {
		drawGrupo(filhos[i]);
	}

	glPopMatrix();
}



void drawGrupos() {
	for (int i = 0; i < gruposLista.size(); i++) {
		drawGrupo(gruposLista[i]);
	}
}





//funcao que desenha os eixos
void eixo() {
	glBegin(GL_LINES);
	// X axis in red
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-100.0f, 0.0f, 0.0f);
	glVertex3f(100.0f, 0.0f, 0.0f);
	// Y Axis in Green
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, -100.0f, 0.0f);
	glVertex3f(0.0f, 100.0f, 0.0f);
	// Z Axis in Blue
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, -100.0f);
	glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
}



void renderScene(void) {

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//modo de desenho, começa com linhas por defeito
	glPolygonMode(GL_FRONT_AND_BACK, tipo);
	

	glLoadIdentity();
	gluLookAt(camX, camY, camZ,
		lookX, lookY, lookZ,
		upX, upY, upZ);


	//desenhar eixos caso seja true
	if (eixos) {
		eixo();
	}

	//cor do desenho
	//glColor3f(v, g, b);

	//desenhar a figura
	drawGrupos();

	glutSwapBuffers();

}


//funcao que processa as teclas do rato e muda as coordenadas, angulos ou raio da camara com base nisso
void processMouseButtons(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) {
		xInicial = x;
		yInicial = y;
		if (button == GLUT_LEFT_BUTTON)		modoRato = 1; //modo rodar camara
		else if (button == GLUT_RIGHT_BUTTON)  modoRato = 2; //modo aproximar ou afastar camara
		else modoRato = 0;
	}
	else if (state == GLUT_UP) {
		if (modoRato == 1) { //muda alpha e beta pois este modo muda a posicao
			alpha += (x - xInicial); 
			beta += (y - yInicial);
		}
		else if (modoRato == 2) { //muda raio pois este modo muda o zoom
			r -= y - yInicial;
			if (r < 3) r = 3.0;
		}
		modoRato = 0;
	}
}


//funcao que faz a movimentacao das variaveis da camara
void processMouseMotion(int x, int y)
{
	int xAux, yAux;
	int alphaAux, betaAux;
	int rAux;

	if (!modoRato) return;

	xAux = x - xInicial;
	yAux = y - yInicial;

	if (modoRato == 1) { 

		alphaAux = alpha + xAux;
		betaAux = beta + yAux;
		if (betaAux > 85.0) betaAux = 85.0;
		else if (betaAux < -85.0) betaAux = -85.0;
		rAux = r;
	}
	else if (modoRato == 2) {

		alphaAux = alpha;
		betaAux = beta;
		rAux = r - yAux;
		if (rAux < 3) rAux = 3;
	}
	//nova posicao x,y,z da camara
	camX = rAux * sin(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camZ = rAux * cos(-alphaAux * M_PI / 180.0) * cos(betaAux * M_PI / 180.0);
	camY = rAux * sin(betaAux * M_PI / 180.0);
}




//funcao que lê cada ficheiro .3d a partir do seu caminho
//preenchendo a lista de pontos com os pontos lidos do ficheiro

list<Ponto> readFile(string caminho3d) {
	string linha;
	vector<string> coordenadas;
	list<Ponto> pontosLista;
	
	//abrir o ficheiro
	ifstream file(caminho3d);
	if (file.is_open()) {
		
		//pega na primeira linha que é o número de vértices ou seja numero de linhas a ler (1 vertice por linha)
		getline(file, linha);                   
		int nLinhas = atoi(linha.c_str());        
		for (int i = 1; i <= nLinhas; i++) {
			getline(file, linha);     //pegar na linha atual
			stringstream ss(linha);		
			vector<string> result{
				istream_iterator<string>(ss), {}    //separar a linha nos espaços e guardar como array de strings em result
			};
			pontosLista.push_back(Ponto(stof(result[0]), stof(result[1]), stof(result[2]))); //adiciona o Ponto lido à lista de pontos
		}

		return pontosLista;
	}
	else { cout << "Erro ao ler o ficheiro .3d" << endl; }
}


void readGrupo(Grupo* grupo, XMLElement* elementoXml) {


	int linhaTrans = -1, linhaRot = -1, linhaScale = -1;
	XMLElement* elementoAux = elementoXml->FirstChildElement("transform");

	XMLElement* translacaoElemento = elementoAux->FirstChildElement("translate");
	if (translacaoElemento != nullptr) {

		cout << "translate" << endl;
		linhaTrans = translacaoElemento->GetLineNum();

		float x = 0, y = 0, z = 0;
		if (translacaoElemento->Attribute("x") != nullptr) {
			x = stof(translacaoElemento->Attribute("x"));
		}
		if (translacaoElemento->Attribute("y") != nullptr) {
			y = stof(translacaoElemento->Attribute("y"));
		}
		if (translacaoElemento->Attribute("z") != nullptr) {
			z = stof(translacaoElemento->Attribute("z"));
		}
		cout << x << endl;
		cout << y << endl;
		cout << z << endl;
		Translacao t = *new Translacao(x, y, z);
		(*grupo).setTranslacao(t);
	}


	XMLElement* rotacaoElemento = elementoAux->FirstChildElement("rotate");
	if (rotacaoElemento != nullptr) {


		linhaRot = rotacaoElemento->GetLineNum();

		float angulo = 0, x = 0, y = 0, z = 0;
		if (rotacaoElemento->Attribute("angle") != nullptr) {
			angulo = stof(rotacaoElemento->Attribute("angle"));
		}
		if (rotacaoElemento->Attribute("x") != nullptr) {
			x = stof(rotacaoElemento->Attribute("x"));
		}
		if (rotacaoElemento->Attribute("y") != nullptr) {
			y = stof(rotacaoElemento->Attribute("y"));
		}
		if (rotacaoElemento->Attribute("z") != nullptr) {
			z = stof(rotacaoElemento->Attribute("z"));
		}
		Rotacao r = *new Rotacao(x, y, z, angulo);
		(*grupo).setRotacao(r);

	}


	XMLElement* escaloElemento = elementoAux->FirstChildElement("scale");
	if (escaloElemento != nullptr) {

		linhaScale = escaloElemento->GetLineNum();

		float x = 0, y = 0, z = 0;
		if (escaloElemento->Attribute("x") != nullptr) {
			x = stof(escaloElemento->Attribute("x"));
		}
		if (escaloElemento->Attribute("y") != nullptr) {
			y = stof(escaloElemento->Attribute("y"));
		}
		if (escaloElemento->Attribute("z") != nullptr) {
			z = stof(escaloElemento->Attribute("z"));
		}
		Escala e = *new Escala(x, y, z);
		(*grupo).setEscala(e);

	}


	XMLElement* modelosXML = elementoXml->FirstChildElement("models");

	if (modelosXML != nullptr) {
		XMLElement* modeloAtualXML = modelosXML->FirstChildElement("model");

		while (modeloAtualXML != nullptr) {

			Modelo modelAtual = *new Modelo();

			if (strcmp(modeloAtualXML->Attribute("file"), "sphere.3d") == 0) {
				cout << "Encontrei sphere" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF2\\3dFiles\\sphere.3d"));
				(*grupo).addModelo(modelAtual);
			}
			if (strcmp(modeloAtualXML->Attribute("file"), "cone.3d") == 0) {
				cout << "Encontrei cone" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF2\\3dFiles\\cone.3d"));
				(*grupo).addModelo(modelAtual);
			}

			if (strcmp(modeloAtualXML->Attribute("file"), "plane.3d") == 0) {
				cout << "Encontrei plane" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF2\\3dFiles\\plane.3d"));
				(*grupo).addModelo(modelAtual);

			}
			if (strcmp(modeloAtualXML->Attribute("file"), "box.3d") == 0) {
				cout << "Encontrei box" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF2\\3dFiles\\box.3d"));
				(*grupo).addModelo(modelAtual);
			}
			modeloAtualXML = modeloAtualXML->NextSiblingElement();
		}
	}

	string o = "";

	if (linhaTrans <= linhaRot && linhaTrans <= linhaScale) {
		if (linhaRot <= linhaScale) {
			o = "T R E";
		}
		else {
			o = "T E R";
		}
	}

	if (linhaRot <= linhaTrans && linhaRot <= linhaScale) {
		if (linhaTrans <= linhaScale) {
			o = "R T E";
		}
		else {
			o = "R E T";
		}
	}

	if (linhaScale <= linhaTrans && linhaScale <= linhaRot) {
		if (linhaRot <= linhaTrans) {
			o = "E R T";
		}
		else {
			o = "E T R";
		}
	}

	(*grupo).setOrdem(o);

	XMLElement* filhos = elementoXml->FirstChildElement("group");

	while (filhos != nullptr) {

		Grupo filho = *new Grupo();
		readGrupo(&filho, filhos);
		(*grupo).addFilho(filho);

		filhos = filhos->NextSiblingElement();
	}
}


//funcao que le o ficheiro.xml da pasta ../xml/ 
void readXML(string file) {
	XMLDocument xml;
	XMLDocument xmltv;
	string s;
	if (!(xml.LoadFile(("C:\\Users\\Miguel\\Desktop\\CGF2\\xml\\" + file).c_str())) && !(xmltv.LoadFile(("C:\\Users\\Miguel\\Desktop\\CGF2\\xml\\" + file).c_str()))) {  //condicao que carrega o ficheiro e testa se é válido
		cout << "Ficheiro lido com sucesso" << endl;

		XMLElement* elemento = xml.FirstChildElement("world")->FirstChildElement("group");    //pega no elemento world do xml
		while (elemento != nullptr) {                  //avança até ser null
			Grupo g = *new Grupo();
			readGrupo(&g, elemento);									
			gruposLista.push_back(g);
			elemento = elemento->NextSiblingElement();     //avança para o proximo
		}

		//Camara
		XMLElement* tv = xmltv.FirstChildElement("world")->FirstChildElement("camera");
		XMLElement* tv2 = tv->FirstChildElement("position");
		XMLElement* tv3 = tv->FirstChildElement("lookAt");
		XMLElement* tv4 = tv->FirstChildElement("up");
		XMLElement* tv5 = tv->FirstChildElement("projection");

		camX = atof(tv2->Attribute("x"));
		camY = atof(tv2->Attribute("y"));
		camZ = atof(tv2->Attribute("z"));

		xInicial = camX;
		yInicial = camY;

		lookX = atof(tv3->Attribute("x"));
		lookY = atof(tv3->Attribute("y"));
		lookZ = atof(tv3->Attribute("z"));

		upX = atof(tv4->Attribute("x"));
		upY = atof(tv4->Attribute("y"));
		upZ = atof(tv4->Attribute("z"));

		fov = atof(tv5->Attribute("fov"));
		near = atof(tv5->Attribute("near"));
		far = atof(tv5->Attribute("far"));

		cout << "POSITION\n" << endl;
		cout << camX << "\n" << endl;
		cout << camY << "\n" << endl;
		cout << camZ << "\n" << endl;

		cout << "LOOK \n" << endl;
		cout << lookX << "\n" << endl;
		cout << lookY << "\n" << endl;
		cout << lookZ << "\n" << endl;

		cout << "UP\n" << endl;
		cout << upX << "\n" << endl;
		cout << upY << "\n" << endl;
		cout << upZ << "\n" << endl;

		cout << "Projection\n" << endl;
		cout << fov << "\n" << endl;
		cout << near << "\n" << endl;
		cout << far << "\n" << endl;
	}

	else {
		cout << "Erro ao ler o xml" << endl;
	}
	return;
}


//funcao que dá função ás teclas premidas
void keyboard(unsigned char key, int x, int y)
{
	if (key == 'e') {
		eixos = !eixos;
	}
	if (key == 'f') {
		tipo = GL_FILL;
	}
	if (key == 'l') {
		tipo = GL_LINE;
	}
	if (key == 'p') {
		tipo = GL_POINT;
	}

	if (key == 'r') {
		v = 1.0f;
		g = 0.0f;
		b = 0.0f;

	}
	if (key == 'g') {
		v = 0.0f;
		g = 1.0f;
		b = 0.0f;
	}
	if (key == 'b') {
		v = 0.0f;
		g = 0.0f;
		b = 1.0f;
	}
	if (key == 'w') {
		v = 1.0f;
		g = 1.0f;
		b = 1.0f;
	}


	glutPostRedisplay();

}




int main(int argc, char* argv[]) {

	if (argc == 2) {
		readXML(argv[1]);
	}
	else {
		readXML("demo.xml");
	}


	// inicialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Phase 2");

	// callback registration 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);

	// OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle 
	glutMainLoop();
}