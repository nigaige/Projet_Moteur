#include "Mesh.h"

Mesh::Mesh(D3DPRIMITIVETYPE primitivMethode)
{
	primitivMethode_ = primitivMethode;
}

void Mesh::addVertex(CUSTOMVERTEX* v)
{
	vertex_.push_back(v);
}
