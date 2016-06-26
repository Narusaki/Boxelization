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

	struct PathInfo
	{
		int nodeId;
	};
	SimpleSceneGraph();
	~SimpleSceneGraph();

	bool LoadModel(std::string modelsDirectory);
	bool LoadPath(std::string pathFile);
	void Render();
	// set for the rotating angle in each refreshment
	void SetRotateSpeed(double rotateSpeed_) {
		rotateSpeed = rotateSpeed_;
	};
	void UpdateRotateState() {
		// TODO: check if the rotate upper bound is met
		// TODO: if it is, change centerNodeId and rotateNodeId according to pathInfo
		// TODO: otherwise, simply update rotateAngle (just like following);
		rotateAngle += rotateSpeed;
	}


private:
	void RenderNode(int nodeId);

private:
	std::vector< SGNode > nodes;
	std::vector< std::list< int > > sceneGraph;
	std::vector< bool > isDFSVisited;
	int rootId;
	double mvMatrix[16];

	double rotateSpeed = 0.0;
	double rotateAngle = 0.0;

	// path information
	std::vector< PathInfo > pathInfo;						// loaded path information
	int centerNodeId = -1, rotateNodeId = -1;				// current center and orbiting node
	int rotateAngleUpperBound = 90.0;						// the maximum rotating angle upper bound
};
#endif