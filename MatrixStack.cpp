#include "MatrixStack.h"

using namespace std;

void MatrixStack::PushMVMatrix()
{
	Matrix m;
	glGetDoublev(GL_MODELVIEW_MATRIX, m.matrix);
	s.push(m);
}

void MatrixStack::PopMVMatrix()
{
	auto m = s.top();
	s.pop();
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(m.matrix);
}