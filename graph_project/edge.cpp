#include "vertex.h"
#include "edge.h"
using namespace std;

Edge::Edge(Vertex* input_Vs, Vertex* input_Vt, int input_Id) {
	Vs = input_Vs;
	Vt = input_Vt;
	Id = input_Id;
}
Vertex* Edge:: getEdgeVs() {
	return Vs;
}
Vertex* Edge::getEdgeVt() {
	return Vt;
}
int Edge::getEdgeId() {
	return Id;
}

