#include "graph.h"
#include <iostream>
#include <string.h>

using namespace std;
Graph::Graph(int Size) {
	/*if (Size <= 10) {
		(*vertices)[Size];
		edges[(Size*(Size - 1)) / 2];
		countV = 0;
		countE = 0;
		size = Size;
	}else{
		cout << "Size of garph is bigger then 10 to make it bigger go to graph.cpp and chance the size" << endl;
	}*/
	countV = 0;
	countE = 0;
	size = Size;
	edges = new vector<Edge*>[Size];
};
Vertex* Graph:: getV(int V) {
	if (vertices.at(V) != NULL) {
		return vertices.at(V);
	}
	else {
		cout << "the vertex doesn't exist"<<endl;
	}

};
Edge* Graph::getE(int Vs,int Index ) {
	try {
		return edges[Vs].at(Index);
	}
	catch (const std::out_of_range& oor) {
		return NULL;
	}

};
void Graph::setV(int x, int y, int z) {
	if (countV < size) {
		vertices.push_back(new Vertex(x, y, z));
		countV++;
	}
	else {
		cout << "graph capasity is full can't put vertex: " <<countV+1<< endl;
	}
}
void Graph::setE(int V1, int V2) {
	if (vertices.at(V1) != NULL && vertices.at(V2) != NULL) {
		edges[V1].push_back (new Edge(vertices.at(V1), vertices.at(V2),stoi(to_string(V1) + to_string(V2))));
		edges[V2].push_back(new Edge(vertices.at(V2), vertices.at(V1), stoi(to_string(V2) + to_string(V1))));
		countE++;
	}
	else {
		cout << "no such V1 or V2" << endl;
	}

}
int Graph::getCountV() {
	return countV;
}

int Graph::getCountE() {
	return countE;
}
void Graph::DFSRecartion(int index, vector<bool>* visited,Vertex* Vt) {
	(*visited)[index] = true;
	if (index == Vt->getVertexId()) return;
	vector<Edge*>::iterator it;
	for (it = edges[index].begin(); it != edges[index].end(); ++it) {
		if (!(*visited)[((*it)->getEdgeVt())->getVertexId()])
			DFSRecartion(((*it)->getEdgeVt())->getVertexId(), visited,Vt);
	}

}

vector<bool> Graph::searchDFS(Vertex* Vs, Vertex* Vt) {
	 vector<bool> visited(countV);
	for (int i = 0; i < countV; i++)
		visited[i] = false;
//	for (int i = Vs->getVertexId(); i < countV; i++)
//		if (visited[i] == false)
	if(Vs!=NULL && Vt!=NULL)
		DFSRecartion(Vs->getVertexId(), &visited,Vt);
	if (Vs != NULL && Vt != NULL) {
		if (visited[Vt->getVertexId()] == false) {
			for (int i = 0; i < countV; i++)
				visited[i] = false;
		}
	}
	return visited;
}