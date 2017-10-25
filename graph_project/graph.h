#include <string.h>
#include "vertex.h"
#include "edge.h"
#include <vector>
using namespace std;
class Graph {
private:
	int countV,countE, size;
	vector<Vertex*> vertices;
	vector<Edge*> *edges;
public:
	Graph(int Size);
	Vertex* getV(int V);
	Edge* getE(int Vs,int Index);
	void setV(int x, int y, int z);
	void setE(int V1, int V2);
	int getCountE();
	int getCountV();
	vector<bool> searchDFS(Vertex* Vs, Vertex* Vt);
	void DFSRecartion(int index, vector<bool>* visited,Vertex* Vt);


};