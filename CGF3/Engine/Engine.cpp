#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>
#include <fstream>
#include <string.h> 

#include "tinyxml2.h"
#include "headers/grupo.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace tinyxml2;
using namespace std;

float camX = 1, camY = 1, camZ = 20;  //posicao x,y,z da camara
int alpha = 0, beta = 0, r = 20;      // angulos e raio da camara
int xInicial, yInicial, modoRato = 0;   //posicoes anteriores da camara e modo da mesma

bool eixos = true;   //eixos
int tipo = GL_LINE;   //tipo de desenho linhas, pontos ou fill
float v = 0.0f, g = 1.0f, b = 0.0f; //cores do desenho

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
	gluPerspective(45, ratio, 1, 1000);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void aplicaRotacao(Rotacao rot) {

	float aux, anguloRot;
	int tempoPrograma;

	if (rot.getTempo() != 0) {
		tempoPrograma = glutGet(GLUT_ELAPSED_TIME);
		aux = tempoPrograma % (int)(rot.getTempo() * 1000);
		anguloRot = (aux * 360) / (rot.getTempo() * 1000);
		glRotatef(anguloRot, rot.getX(), rot.getY(), rot.getZ());
	}
}

void drawGrupo(Grupo g) {

	// obtenção da informação do grupo passado como arugmento

	Translacao t = g.getTranslacao();
	Rotacao r = g.getRotacao();
	Escala e = g.getEscala();
	string ordem = g.getOrdem();
	vector<Grupo> filhos = g.getFilhos();
	vector<Modelo> m = g.getModelos();

	glPushMatrix();

	// executar as tranformações pela ordem correta

	for (int i = 0; i < 5; i += 2) {
		switch (ordem[i]) {
		case 'T':
			if (t.getPontos().size() == 0) {
				glTranslatef(t.getX(), t.getY(), t.getZ());
			}
			else {
				glColor3f(1.0f, 1.0f, 1.0f);
				t.draw();
			}
			break;
		case 'R':
			if (r.getAngulo() != 0) {
				glRotatef(r.getAngulo(), r.getX(), r.getY(), r.getZ());
			}
			else {
				aplicaRotacao(r);
			}
			break;
		case 'E':
			glScalef(e.getX(), e.getY(), e.getZ());
			break;
		default:
			break;
		}
	}


	for (int i = 0; i < m.size(); i++) {
		glColor3f(m[i].getR(), m[i].getG(), m[i].getB());
		Modelo aux = m[i];
		aux.draw();
	}

	for (int i = 0; i < filhos.size(); i++) {
		drawGrupo(filhos[i]);
	}

	glPopMatrix();
}



void drawGrupos() {
	for (int i = 0; i < gruposLista.size(); i++) { // vai individualmente a cada grupo principal, que estao alocados globalmente no vetor gruposLista
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
		0.0, 0.0, 0.0,
		0.0f, 1.0f, 0.0f);


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

vector<float> readFile(string caminho3d) {
	string linha;
	vector<string> coordenadas;
	vector<float> pontosLista;

	//abrir o ficheiro
	ifstream file(caminho3d);
	if (file.is_open()) {

		//pega na primeira linha que é o número de vértices ou seja numero de linhas a ler (3 vertice por linha)
		getline(file, linha);
		int nLinhas = atoi(linha.c_str());
		for (int i = 1; i <= nLinhas; i++) {
			getline(file, linha);     //pegar na linha atual
			stringstream ss(linha);
			vector<string> result{
				istream_iterator<string>(ss), {}    //separar a linha nos espaços e guardar como array de strings em result
			};
			pontosLista.push_back(stof(result[0]));
			pontosLista.push_back(stof(result[1]));
			pontosLista.push_back(stof(result[2]));
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

		linhaTrans = translacaoElemento->GetLineNum();

		float tempo = 0;
		float x, y, z;
		x = y = z = 0;
		vector <Ponto> pontosCatmull;

		if (translacaoElemento->Attribute("time") != nullptr) {


			tempo = stof(translacaoElemento->Attribute("time"));
			XMLElement* pontos = translacaoElemento->FirstChildElement("point");

			while (pontos != nullptr) {

				if (pontos->Attribute("x") != nullptr) {
					x = stof(pontos->Attribute("x"));
				}
				if (pontos->Attribute("y") != nullptr) {
					y = stof(pontos->Attribute("y"));
				}
				if (pontos->Attribute("z") != nullptr) {
					z = stof(pontos->Attribute("z"));
				}

				pontosCatmull.push_back(*new Ponto(x, y, z));
				pontos = pontos->NextSiblingElement();
			}

			Translacao t = *new Translacao(tempo, pontosCatmull);
			(*grupo).setTranslacao(t);
		}

		else {

			if (translacaoElemento->Attribute("x") != nullptr) {
				x = stof(translacaoElemento->Attribute("x"));
			}
			if (translacaoElemento->Attribute("y") != nullptr) {
				y = stof(translacaoElemento->Attribute("y"));
			}
			if (translacaoElemento->Attribute("z") != nullptr) {
				z = stof(translacaoElemento->Attribute("z"));
			}
			Translacao t = *new Translacao(x, y, z);
			(*grupo).setTranslacao(t);
		}
	}


	XMLElement* rotacaoElemento = elementoAux->FirstChildElement("rotate");
	if (rotacaoElemento != nullptr) {


		linhaRot = rotacaoElemento->GetLineNum();

		float tempo = 0, x = 0, y = 0, z = 0, angulo = 0;
		if (rotacaoElemento->Attribute("time") != nullptr) {
			tempo = stof(rotacaoElemento->Attribute("time"));
		}
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
		Rotacao r = *new Rotacao(x, y, z, tempo, angulo);
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

			float r = 0.0f, g = 0.0f, b = 0.0f;
			if (modeloAtualXML->Attribute("R") != nullptr) {
				r = stof(modeloAtualXML->Attribute("R"));
			}
			if (modeloAtualXML->Attribute("G") != nullptr) {
				g = stof(modeloAtualXML->Attribute("G"));
			}
			if (modeloAtualXML->Attribute("B") != nullptr) {
				b = stof(modeloAtualXML->Attribute("B"));
			}

			modelAtual.setR(r);
			modelAtual.setG(g);
			modelAtual.setB(b);

			if (strcmp(modeloAtualXML->Attribute("file"), "sphere.3d") == 0) {
				cout << "Encontrei sphere" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF3\\3dFiles\\sphere.3d"));

			}
			if (strcmp(modeloAtualXML->Attribute("file"), "cone.3d") == 0) {
				cout << "Encontrei cone" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF3\\3dFiles\\cone.3d"));
			}

			if (strcmp(modeloAtualXML->Attribute("file"), "plane.3d") == 0) {
				cout << "Encontrei plane" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF3\\3dFiles\\plane.3d"));


			}
			if (strcmp(modeloAtualXML->Attribute("file"), "box.3d") == 0) {
				cout << "Encontrei box" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF3\\3dFiles\\box.3d"));

			}
			if (strcmp(modeloAtualXML->Attribute("file"), "bezier.3d") == 0) {
				cout << "Encontrei bezier" << endl;
				modelAtual.setPontos(readFile("C:\\Users\\Miguel\\Desktop\\CGF3\\3dFiles\\bezier.3d"));

			}

			modelAtual.prepareData();
			(*grupo).addModelo(modelAtual);
			modeloAtualXML = modeloAtualXML->NextSiblingElement();
		}
	}

	//int linhaTrans = -1, linhaRot = -1, linhaScale = -1;

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
	cout << "sai" << endl;


}


//funcao que le o ficheiro.xml da pasta ../xml/ 
void readXML(string file) {
	XMLDocument xml;
	XMLDocument xmltv;
	string s;
	if (!(xml.LoadFile(("C:\\Users\\Miguel\\Desktop\\CGF3\\xml\\" + file).c_str())) && !(xmltv.LoadFile(("C:\\Users\\Miguel\\Desktop\\CGF3\\xml\\" + file).c_str()))) {  //condicao que carrega o ficheiro e testa se é válido

		cout << "Ficheiro lido com sucesso" << endl;

		XMLElement* elemento = xml.FirstChildElement("world")->FirstChildElement("group");    //pega no elemento scene do xml
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


		lookX = atof(tv3->Attribute("x"));
		lookY = atof(tv3->Attribute("y"));
		lookZ = atof(tv3->Attribute("z"));

		upX = atof(tv4->Attribute("x"));
		upY = atof(tv4->Attribute("y"));
		upZ = atof(tv4->Attribute("z"));

		fov = atof(tv5->Attribute("fov"));
		near = atof(tv5->Attribute("near"));
		far = atof(tv5->Attribute("far"));
		
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

	glutPostRedisplay();

}




int main(int argc, char* argv[]) {


	// inicialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Phase 3");


	// callback registration 
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);
	glutReshapeFunc(changeSize);

	// mouse callbacks
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutKeyboardFunc(keyboard);

	glewInit();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);

	if (argc == 2) {
		readXML(argv[1]);
	}
	else {
		readXML("demo.xml");
	}

	// enter GLUT's main cycle 
	glutMainLoop();
}