#define vertex_H

using namespace std;

class Edge {
	private:
		Vertex* Vs;
		Vertex* Vt;
		int Id;
	public:
		Edge(Vertex* Vs, Vertex* Vt, int Id);
		Vertex* getEdgeVs();
		Vertex* getEdgeVt();
		int  getEdgeId();

};