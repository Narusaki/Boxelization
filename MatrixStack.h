#ifndef MATRIXSTACK_H
#define MATRIXSTACK_H

#include <Windows.h>
#include <gl/GL.h>
#include <stack>

class MatrixStack
{
public:
	struct Matrix
	{
		double matrix[16];
	};

	void PushMVMatrix();
	void PopMVMatrix();

private:
	std::stack< Matrix > s;
};
#endif