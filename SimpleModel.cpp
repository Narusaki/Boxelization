#include <Windows.h>
#include <gl\GL.h>
#include "SimpleModel.h"
#include <fstream>
#include <sstream>

using namespace std;

SimpleModel::SimpleModel()
{

}

SimpleModel::SimpleModel(const SimpleModel& m)
{
	verts = m.verts;
	faces = m.faces;
}

SimpleModel::~SimpleModel()
{

}

bool SimpleModel::LoadMesh(string fileName)
{
	if (fileName.substr(fileName.rfind("."), 4) == ".obj" || fileName.substr(fileName.rfind("."), 4) == ".OBJ")
		return LoadOBJ(fileName);
	if (fileName.substr(fileName.rfind("."), 4) == ".off" || fileName.substr(fileName.rfind("."), 4) == ".OFF")
		return LoadOFF(fileName);
	else return false;
	return true;
}

bool SimpleModel::LoadOBJ(string fileName)
{
	ifstream input(fileName);
	if (!input) return false;
	string curLine;
	Vector3D p; int v0, v1, v2;
	stringstream sin;
	char typeHeader;
	while (getline(input, curLine))
	{
		sin.clear();
		if (curLine.substr(0, 2) == "v ")
		{
			sin << curLine;
			sin >> typeHeader >> p.x >> p.y >> p.z;
			verts.push_back(p);
		}
		else if (curLine.substr(0, 2) == "f ")
		{
			sin << curLine;
			sin >> typeHeader >> v0 >> v1 >> v2;
			faces.push_back(v0-1); faces.push_back(v1-1); faces.push_back(v2-1);
		}
	}
	return true;
}
bool SimpleModel::LoadOFF(string fileName)
{
	ifstream input(fileName);
	if (!input) return false;
	string curLine;
	int nVert, nFace, nEdge;
	int polyType;
	stringstream sin;
	getline(input, curLine);	// OFF
	getline(input, curLine);	// nVert, nFace, nEdge
	sin << curLine;
	sin >> nVert >> nFace >> nEdge;

	verts.resize(nVert); faces.resize(nFace * 3);
	for (int i = 0; i < nVert; ++i)
	{
		sin.clear();
		getline(input, curLine);
		sin << curLine;
		sin >> verts[i].x >> verts[i].y >> verts[i].z;
	}
	for (int i = 0; i < nFace; ++i)
	{
		sin.clear();
		getline(input, curLine);
		sin << curLine;
		sin >> polyType >> faces[i * 3] >> faces[i * 3 + 1] >> faces[i * 3 + 2];
	}
	return true;
}

void SimpleModel::Normalize()
{
	Vector3D vMin(DBL_MAX, DBL_MAX, DBL_MAX), vMax(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	Vector3D center;
	for (auto &p : verts)
	{
		center += p;
		for (int i = 0; i < 3; ++i) vMin[i] = __min(vMin[i], p[i]);
		for (int i = 0; i < 3; ++i) vMax[i] = __max(vMax[i], p[i]);
	}
	center /= verts.size();
	double scale = 1.0 / ((vMin - vMax).length() / 2.0);
	Normalize(center, scale);
}

void SimpleModel::Normalize(Vector3D center, double scale)
{
	for (auto &p : verts)
		p = (p - center) * scale;
}

void SimpleModel::Render()
{
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i += 3)
	{
		for (int j = 0; j < 3; ++j)
			glVertex3d(verts[faces[i + j]].x, verts[faces[i + j]].y, verts[faces[i + j]].z);
	}
	glEnd();
}