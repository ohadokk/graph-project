#include <stdlib.h>
#include <math.h>
#define _USE_MATH_DEFINES


#include <time.h>
enum {up,down};

#include <thread>

#include <iostream>
#ifdef WIN32
#include <windows.h>
#endif


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "graph.h"

#define SIZE 10 
//input for console
int num = 1;//vertex coordinate
char consoleChar = NULL;//exit edge connection
int v1, v2;//vertecx to connect 

float zpos = 0.0f;
int Side=0;

// angle of rotation for the camera direction
float angleX = 0.0f;
float angleY = 0.0f;

// actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f , ly=0.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f,y=1.0f;

// the key states. These variables will be zero
//when no key is being presses
float deltaAngleX = 0.0f;
float deltaAngleY = 0.0f;
float deltaMove = 0;

//for keyboard function for rotating the graph 
float XrotAngle = 0;
float YrotAngle = 0;
float ZrotAngle = 0;

//keyboard values added to variables for rotating 
float xRotate = 0.0f;
float yRotate = 0.0f;
float zRotate = 0.0f;

int xOrigin = -1;
int yOrigin = 0;

//variables for tarnslation
float xTranslate = 0.0f;
float yTranslate = 0.0f;
float zTranslate = 0.0f;


//flag for swich keboard from rotate to tanslate
bool rotFlag = true;

Graph* G=new Graph(SIZE);
HWND textbox;


int searchIndex=0;
Vertex *SearchedVertex;
Vertex *chooseV1 = NULL;
Vertex *chooseV2 = NULL;
bool makepath = false;
void searchveretx(int direction) {
	if (direction == up) {
		if (searchIndex < G->getCountV()) {
			SearchedVertex = (G->getV(searchIndex));
			searchIndex++;
		}
		else searchIndex = 0;
	}
	if (direction == down) {
		if (searchIndex >0) {
			SearchedVertex = (G->getV(searchIndex));
			searchIndex--;
		}
		else searchIndex = SIZE-1;
	}
}
void ChooseVertex() {
	if (chooseV1 == NULL) {
		chooseV1 = SearchedVertex;
	}
	else if (chooseV2==NULL) {
		chooseV2 = SearchedVertex;
		makepath == true;
	}
	else {
		makepath == false;
		chooseV1 = NULL;
		chooseV2 = NULL;
	}

}


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void ColorGraph(int i, vector<bool> DFSpath) {
	if (SearchedVertex == G->getV(i)) glColor3f(1.0f, 0.0f, 0.5f);	
	else if (chooseV1 == G->getV(i)) glColor3f(1.0f, 0.0f, 0.0f);
	else if (chooseV2 == G->getV(i)) glColor3f(0.0f, 1.0f, 0.0f);
	else if(DFSpath[i] == true)
		glColor3f(0.7f, 0.3f, 0.2f);
	else
		glColor3f(0.5f, 0.5f, 0.5f);
}


void drawGraph() {
	
	//for (int i = 0; i < G->getCountV; i++) {
	glColor3f(0.5f, 0.5f, 0.5f);
	//glutSolidSphere(0.75f, 20, 20);
	Edge *EdgeIndex;
	vector<bool> path = G->searchDFS(chooseV1, chooseV2
	);
	for (int i = 0; i < G->getCountV(); i++) {
		glPushMatrix();
		ColorGraph(i, path);
		glTranslatef((G->getV(i))->getVertexX(), (G->getV(i))->getVertexY(), (G->getV(i))->getVertexZ());
		glutSolidSphere(0.5f, 20, 20);
		glPopMatrix();
	}
	for (int i = 0; i < G->getCountE(); i++) {
		for (int j = 0; j < G->getCountE(); j++) {
			glColor3f(0.5f, 0.5f, 0.5f);
			EdgeIndex = (G->getE(i, j));
			if (EdgeIndex == NULL) break;
			glBegin(GL_LINES);
			glVertex3f(EdgeIndex->getEdgeVs()->getVertexX(), EdgeIndex->getEdgeVs()->getVertexY(), EdgeIndex->getEdgeVs()->getVertexZ());
			glVertex3f(EdgeIndex->getEdgeVt()->getVertexX(), EdgeIndex->getEdgeVt()->getVertexY(), EdgeIndex->getEdgeVt()->getVertexZ());
			glEnd();
		}
	}	
}

void computeForward(float deltaMove) {

	x += deltaMove * lx * 0.1f;
	z += deltaMove * lz * 0.1f;
	y += deltaMove * ly * 0.1f;
}
void rotate() {
		xRotate += XrotAngle * 0.2 ;
		yRotate += YrotAngle * 0.2 ;
		zRotate += ZrotAngle * 0.2 ;
		
}

void renderScene(void) {

	if (deltaMove) {
		computeForward(deltaMove);
		deltaMove = 0;
	}
	
	rotate();

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	// Reset transformations
	glLoadIdentity();
	glTranslatef(xTranslate, yTranslate, zTranslate);
	// Set the camera
	gluLookAt(x, y, z,
		x + lx, y+ly, z + lz,
		0.0f, 1.0f, 0.0f);
	glRotatef(xRotate, 1.0f, 0.0f, 0.0f);
	glRotatef(yRotate, 0.0f, 1.0f, 0.0f);
	glRotatef(zRotate, 0.0f, 0.0f, 1.0f);
	
	// Draw ground

	//glColor3f(0.9f, 0.9f, 0.9f);
	//glBegin(GL_QUADS);
	//glVertex3f(-100.0f, 0.0f, -100.0f);
	//glVertex3f(-100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, -100.0f);
	//glEnd();

	
	// Draw 36 SnowMen
	drawGraph();
	/*for (int i = -3; i < 3; i++)
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*10.0, 0, j * 10.0);
			drawSnowMan();
			glPopMatrix();
		}*/
	glutSwapBuffers();
}

void pressNormalKeys(unsigned char key, int xx, int yy) {
	switch (key)
	{
	case 27:
		exit(0); break;
	case 'w':
		if (rotFlag) {
			YrotAngle = -1;
		}
		else
			yTranslate += 0.5;
		break;
	case 's':
		if (rotFlag)
			YrotAngle = -1;
		else
			yTranslate -= 0.5;
		break;
	case 'a':
		if (rotFlag)
			XrotAngle = -1;
		else
			xTranslate -= 0.5;
		break;
	case 'd':
		if (rotFlag)
			XrotAngle = 1;
		else
			xTranslate += 0.5;
		break;
	case 'q':
		if (rotFlag)
			ZrotAngle = 1;
		else
			zTranslate -= 0.5;
		break;
	case 'e':
		if (rotFlag)
			ZrotAngle = -1;
		else
			zTranslate += 0.5;
		break;
	case 'z':
		rotFlag = true; break;
	case 'x':
		rotFlag = false; break;
	case '/':
		ChooseVertex();

	}
}

void releaseNormalKeys(unsigned char key, int xx, int yy) {
	switch (key)
	{
	case 27:
		exit(0); break;
	case 'w':
		if(rotFlag)
			YrotAngle = 0;
		break;
	case 's':	
		if (rotFlag)
			YrotAngle = 0;
		break;
	case 'a':
		if (rotFlag)
			XrotAngle = 0; 
		break;
	case 'd':
		if (rotFlag)
			XrotAngle = 0; 
		break;
	case 'q':
		if (rotFlag)
			ZrotAngle = 0; 
		break; 
	case 'e':
		if (rotFlag)
			ZrotAngle = 0; 
		break; 
	case 'z':
		break;
	case 'x':
		break;
	}
}

void pressKey(int key, int xx, int yy) {

	
	switch (key) {
	case GLUT_KEY_UP:if (G->getCountV() != 0)searchveretx(up); break;
	case GLUT_KEY_DOWN:if (G->getCountV() != 0)searchveretx(down); break;
	case GLUT_KEY_RIGHT:  break;
	case GLUT_KEY_LEFT:	   break;
	}
}

void releaseKey(int key, int x, int y) {

	switch (key) {
	case GLUT_KEY_UP:break;
	case GLUT_KEY_DOWN: break;
	case GLUT_KEY_RIGHT:  break;
	case GLUT_KEY_LEFT:   break;
	}
	
}

void mouseMove(int x, int y) {

	// this will only be true when the left button is down
	if (xOrigin >= 0) {

		// update deltaAngle
		deltaAngleX = (x - xOrigin) * 0.001f;
		deltaAngleY = (y - yOrigin) * 0.001f;
		// update camera's direction
		lx = sin(angleX - deltaAngleX);
		ly = sin(angleY + deltaAngleY);
		lz = -cos(angleX - deltaAngleX);
	}
}

void mouseButton(int button, int state, int x, int y) {

	// only start motion if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {

		// when the button is released
		if (state == GLUT_UP) {
			angleX -= deltaAngleX;
			angleY += deltaAngleY;
			xOrigin = -1;
			yOrigin = 0;
		}
		else {// state = GLUT_DOWN
			xOrigin = x;
			yOrigin = y;
		}
	}
	if (button == 3) {
		deltaMove = 0.5f;;
	}
	if (button == 4) {
		deltaMove = -1.5f;;
	}
}
void graficinterface() {
	// init GLUT and create window
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(320, 320);
	glutCreateWindow("Lighthouse3D - GLUT Tutorial");
	

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(pressNormalKeys);
	glutKeyboardUpFunc(releaseNormalKeys);
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	// here are the two new functions
	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	//glutCreateWindow("win2");   // Create a window 2
	//glutDisplayFunc(renderScene);   // Register display callback
	//glutReshapeFunc(changeSize);
	//// enter GLUT event processing cycle


	glutMainLoop();
}

void consolemenu() {
	int X, Y, Z;
	while (true) {
		cout << "press v for new vertex || press e for new edge ";
		cin >> consoleChar;
		if (consoleChar == 'v') {
			while (consoleChar != 'x') {
				cout << "enter X coordinate for vertex "<< G->getCountV() << ": ";
				cin >> X;
				cout << "enter Y coordinate for vertex " << G->getCountV() << ": ";
				cin >> Y;
				cout << "enter Z coordinate for vertex " << G->getCountV() << ": ";
				cin >> Z;
				G->setV(X, Y, Z);
				cout << endl << "press x for another option or anything else to enter another vertex " << endl;
				cin >> consoleChar;

			}
			consoleChar = NULL;
		}
		if (consoleChar == 'e') {
			while (consoleChar != 'x') {

				cout << "enter first vertex: ";
				cin >> v1;
				cout << endl << "enter second vertex: ";
				cin >> v2;
				cout << "are you sure you what to connect ? y|n (for another option press x)" << endl;
				cin >> consoleChar;
				if (consoleChar == 'y') {
					G->setE(v1, v2);
				}
				if (consoleChar == 'n')
					continue;

			}
		}
	}
}

int main(int argc, char **argv) {
	/*G->setV(0, 0, 0, "0");
	G->setV(2, 2, 3, "1");
	G->setE(0, 1);*/
	srand(time(NULL));

	G->setV(0, 0, 0);
	for (int i = 1; i < 10; i++) {
		G->setV(rand() % 10, rand() % 10, rand() % 10);
		
	}
	for (int i = 1; i < 10; i++) {
	
		G->setE(rand() % 10, rand() % 10);
	}
	glutInit(&argc, argv);
	
	thread first(graficinterface);
	thread seconde(consolemenu);

	first.join();
	seconde.join();
	
	return 1;
}












