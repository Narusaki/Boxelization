#include "SceneGraph.h"
#include "dirent.h"
#include <iostream>

using namespace std;

SimpleSceneGraph::SimpleSceneGraph()
{

}

SimpleSceneGraph::~SimpleSceneGraph()
{

}

bool SimpleSceneGraph::LoadModel(std::string modelsDirectory)
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(modelsDirectory.c_str())) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			string d_name = ent->d_name;
			if (d_name.substr(d_name.rfind("."), d_name.size() - d_name.rfind(".")) != ".obj" &&
				d_name.substr(d_name.rfind("."), d_name.size() - d_name.rfind(".")) != ".off")
				continue;
			nodes.push_back(SGNode(modelsDirectory + "//" + ent->d_name));
		}
		closedir(dir);
	}
	else {
		return false;
	}

	// normalize
	Vector3D center; int totalVertNum = 0;
	Vector3D vMin(DBL_MAX, DBL_MAX, DBL_MAX), vMax(-DBL_MAX, -DBL_MAX, -DBL_MAX);
	for (auto &node : nodes)
	{
		totalVertNum += node.m.verts.size();
		for (auto &p : node.m.verts)
		{
			center += p;
			for (int i = 0; i < 3; ++i) vMin[i] = __min(vMin[i], p[i]);
			for (int i = 0; i < 3; ++i) vMax[i] = __max(vMax[i], p[i]);
		}
	}
	center /= totalVertNum;
	double scale = 1.0 / ((vMax - vMin).length() / 2.0);
	for (auto &node : nodes) node.m.Normalize(center, scale);
	return true;
}

bool SimpleSceneGraph::LoadPath(std::string pathFile)
{
	return true;
}

void SimpleSceneGraph::Normalize()
{
	for (auto &node : nodes)
	{

	}
}

void SimpleSceneGraph::Render()
{
	for (auto &node : nodes)
	{
		node.Render();
	}
}