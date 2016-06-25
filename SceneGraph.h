/*
This is a simple scene graph used to render hierarchical scene
The scene graph is represented by a adjacent linked table
*/

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "SimpleModel.h"
#include <vector>
#include <list>

// a node of scene graph
class SGNode
{
public:
	SGNode() { 
		for (int i = 0; i < 16; ++i) mvMatrix[i] = i % 5 == 0 ? 1 : 0;
	}
	SGNode(std::string fileName) : SGNode() { 
		m.LoadMesh(fileName);
	}

	SGNode(const SGNode &node) {
		m = node.m;
		memcpy(mvMatrix, node.mvMatrix, sizeof(double) * 16);
	}
	~SGNode() { }

public:
	SimpleModel m;			// model
	Vector3D center;		// pivot center
	double mvMatrix[16];		// rener matrix;
};

class SimpleSceneGraph
{
public:
	SimpleSceneGraph();
	~SimpleSceneGraph();

	bool LoadModel(std::string modelsDirectory);
	bool LoadPath(std::string pathFile);

	void Render();

private:
	void RenderNode(int nodeId);

private:
	std::vector< SGNode > nodes;
	std::vector< std::list< int > > sceneGraph;
	std::vector< bool > isDFSVisited;
	int rootId;
	double mvMatrix[16];
};
#endif