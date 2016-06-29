#include <Windows.h>
#include <gl\GL.h>
#include "SceneGraph.h"
#include "dirent.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

istream& operator>>(istream &in, SimpleSceneGraph::PathInfo &pathInfo)
{
	in >> pathInfo.rotateNodeId >> pathInfo.centerNodeId;
	in >> pathInfo.rotateCenter.x >> pathInfo.rotateCenter.y >> pathInfo.rotateCenter.z;
	in >> pathInfo.rotateAxis.x >> pathInfo.rotateAxis.y >> pathInfo.rotateAxis.z;
	in >> pathInfo.angle;
	return in;
}

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

bool SimpleSceneGraph::LoadConnectivity(std::string connectivityFile)
{
	// Build the adjacent list according to the path. Set root.

	// currently a fully-linked graph is built.
	sceneGraph.resize(nodes.size());
// 	for (int i = 0; i < sceneGraph.size(); ++i)
// 	{
// 		for (int j = 0; j < nodes.size(); ++j)
// 		{
// 			if (j == i) continue;
// 			sceneGraph[i].push_back(j);
// 		}
// 	}

	// WARNING: a complete graph will has a serious problem when rendering (some rotating may be lost)
	// this could be just a tree 
	// use a tree based on the input path (by added extra edges to form a tree) will solve this problem
	// request the input file to provide such a tree

	ifstream input(connectivityFile);
	string l;
	while (getline(input, l))
	{
		int n0, n1;
		stringstream sin;
		sin << l; sin >> n0 >> n1;
		sceneGraph[n0].push_back(n1); sceneGraph[n1].push_back(n0);
	}
	rootId = 0;
	return true;
}

bool SimpleSceneGraph::LoadPath(std::string pathFile)
{
	// TODO: Load the path information. 
	ifstream input(pathFile);
	string l;
	PathInfo curPathInfo;
	while (getline(input, l))
	{
		stringstream sin;
		sin << l; sin >> curPathInfo;
		pathInfos.push_back(curPathInfo);
	}

	curPathInfoIndex = 0;
	return true;
}

void SimpleSceneGraph::Render()
{
	if (rootId == -1) return;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixd(mvMatrix);
	// DFS to render the scene
	isDFSVisited.assign(isDFSVisited.size(), false);
	dfsParentNodeId = -1;
	RenderNode(rootId);
	glPopMatrix();
}

void SimpleSceneGraph::RenderNode(int nodeId)
{
	isDFSVisited[nodeId] = true;
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	if (curPathInfoIndex != -1 && curPathInfoIndex < pathInfos.size())
	{
		// TESTING MODIFICATION OF LOCAL MVMATRIX
		// TODO: if nodeId == rotateNodeId && parentNodeId == centerNodeId
		// TODO: update current node's mvMatrix here
		auto &pathInfo = pathInfos[curPathInfoIndex];
		if (nodeId == pathInfo.rotateNodeId && dfsParentNodeId == pathInfo.centerNodeId)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslated(pathInfo.rotateCenter.x, pathInfo.rotateCenter.y, pathInfo.rotateCenter.z);
			glRotated(rotateAngle, pathInfo.rotateAxis.x, pathInfo.rotateAxis.y, pathInfo.rotateAxis.z);
			glTranslated(-pathInfo.rotateCenter.x, -pathInfo.rotateCenter.y, -pathInfo.rotateCenter.z);
			glGetDoublev(GL_MODELVIEW_MATRIX, nodes[nodeId].mvMatrix);
			glPopMatrix();
		}
		// TODO: otherwise, if nodeId == centerNodeId && parentNodeId == rotateNodeId
		// TODO: "reverse" the rotating matrix and update current node's mvMatrix here
		else if (nodeId == pathInfo.centerNodeId && dfsParentNodeId == pathInfo.rotateNodeId)
		{
			glPushMatrix();
			glLoadIdentity();
			glTranslated(pathInfo.rotateCenter.x, pathInfo.rotateCenter.y, pathInfo.rotateCenter.z);
			glRotated(-rotateAngle, pathInfo.rotateAxis.x, pathInfo.rotateAxis.y, pathInfo.rotateAxis.z);
			glTranslated(-pathInfo.rotateCenter.x, -pathInfo.rotateCenter.y, -pathInfo.rotateCenter.z);
			glGetDoublev(GL_MODELVIEW_MATRIX, nodes[nodeId].mvMatrix);
			glPopMatrix();
		}
	}

	glMultMatrixd(nodes[nodeId].mvMatrix);
	if (curPathInfoIndex != -1 && curPathInfoIndex < pathInfos.size() && 
		nodeId == pathInfos[curPathInfoIndex].rotateNodeId)
		glColor3f(0.0, 1.0, 0.0);
	else if (curPathInfoIndex != -1 && curPathInfoIndex < pathInfos.size() && 
		nodeId == pathInfos[curPathInfoIndex].centerNodeId)
		glColor3f(1.0, 0.0, 0.0);
	else
		glColor3f(0.7, 0.7, 0.7);
	nodes[nodeId].m.Render();
	// recursively render 
	for (auto adjNodeIter = sceneGraph[nodeId].begin(); 
		adjNodeIter != sceneGraph[nodeId].end(); ++adjNodeIter)
	{
		if (isDFSVisited[*adjNodeIter]) continue;
		dfsParentNodeId = nodeId;
		RenderNode(*adjNodeIter);
	}
	glPopMatrix();
}