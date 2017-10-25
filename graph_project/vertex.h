#include <string>

using namespace std;

class Vertex {

private:
	float X, Y, Z;
	int Id;
	static int countV;
public:
	Vertex(float X, float Y, float Z);
	float getVertexX();
	float getVertexY();
	float getVertexZ();
	int getVertexId();

};

