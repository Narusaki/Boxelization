#include <Windows.h>
#include <gl\GL.h>
#include "SceneGraph.h"
#include "dirent.h"
#include <iostream>

using namespace std;

SimpleSceneGraph::SimpleSceneGraph()
{
	for (int i = 0; i < 16; ++i) mvMatrix[i] = i % 5 == 0 ? 1 : 0;
}

SimpleSceneGraph::~SimpleSceneGraph()
{

}

bool SimpleSceneGraph::LoadModel(std::string modelsDirectory)
{
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(modelsDirectory.c_str())) != NULL) 
	{
		while ((ent = readdir(dir)) != NULL) 
		{
			string d_name = ent->d_name;
			if (d_name.substr(d_name.rfind("."), d_name.size() - d_name.rfind(".")) != ".obj" &&
				d_name.substr(d_name.rfind("."), d_name.size() - d_name.rfind(".")) != ".off")
				continue;
			nodes.push_back(SGNode(modelsDirectory + "//" + ent->d_name));
		}
		closedir(dir);
	}
	else 
	{
		return false;
	}

	isDFSVisited.resize(nodes.size(), false);
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
	mvMatrix[0] = scale; mvMatrix[5] = scale; mvMatrix[10] = scale;
	mvMatrix[12] = scale*(-center.x);
	mvMatrix[13] = scale*(-center.y);
	mvMatrix[14] = scale*(-center.z);
	return true;
}

bool SimpleSceneGraph::LoadPath(std::string pathFile)
{
	// TODO: Load the path information. 
	// Build the adjacent list according to the path. Set root.
	
	// currently a fully-linked graph is built.
	sceneGraph.resize(nodes.size());
	for (int i = 0; i < sceneGraph.size(); ++i)
	{
		for (int j = 0; j < nodes.size(); ++j)
		{
			if (j == i) continue;
			sceneGraph[i].push_back(j);
		}
	}
	rootId = 0;
	return true;
}

void SimpleSceneGraph::Render()
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixd(mvMatrix);
	// DFS to render the scene
	isDFSVisited.assign(isDFSVisited.size(), false);
	RenderNode(rootId);
	glPopMatrix();
}

void SimpleSceneGraph::RenderNode(int nodeId)
{
	isDFSVisited[nodeId] = true;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	// TESTING MODIFICATION OF LOCAL MVMATRIX
	glPushMatrix();
	glLoadIdentity();
	glRotated(rotateAngle, 1.0, 0.0, 0.0);
	glGetDoublev(GL_MODELVIEW_MATRIX, nodes[nodeId].mvMatrix);
	glPopMatrix();

	glMultMatrixd(nodes[nodeId].mvMatrix);
	nodes[nodeId].m.Render();
	// recursively render 
	for (auto adjNodeIter = sceneGraph[nodeId].begin(); 
		adjNodeIter != sceneGraph[nodeId].end(); ++adjNodeIter)
	{
		if (isDFSVisited[*adjNodeIter]) continue;
		RenderNode(*adjNodeIter);
	}
	glPopMatrix();
}