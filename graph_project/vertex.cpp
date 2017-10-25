#include "vertex.h"
#include <string>

using namespace std;
Vertex::Vertex(float input_X, float  input_Y, float  input_Z)
{
	X = input_X;
	Y = input_Y;
	Z = input_Z;
	Id =countV;
	countV++;

}

int Vertex::countV = 0;

float Vertex::getVertexX() {
	return X;
}

float Vertex::getVertexY() {
	return Y;
}

float Vertex::getVertexZ() {
	return Z;
}
int Vertex::getVertexId() {
	return Id;
}