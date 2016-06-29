/*
This is a simple scene graph used to render hierarchical scene
The scene graph is represented by a adjacent linked table
*/

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include "SimpleModel.h"
#include "MatrixStack.h"
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
		// TODO: this PathInfo struct should contain all necessary information 
		// TODO: that confirm a definite rotation, including the following: 
		// TODO: the center&orbiting cubes, the center, direction, angle
		int rotateNodeId = -1, centerNodeId = -1;
		Vector3D rotateCenter;
		Vector3D rotateAxis;
		double angle = 0.0;

		friend std::istream& operator>>(std::istream &in, PathInfo &pathInfo);
	};
	SimpleSceneGraph();
	~SimpleSceneGraph();

	bool LoadModel(std::string modelsDirectory);
	bool LoadConnectivity(std::string connectivityFile);
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
		if (curPathInfoIndex >= pathInfos.size()) return;
		if (rotateAngle < pathInfos[curPathInfoIndex].angle)
			rotateAngle += rotateSpeed;
		else if (rotateAngle > pathInfos[curPathInfoIndex].angle)
			rotateAngle = pathInfos[curPathInfoIndex].angle;
		else
		{
			rotateAngle = 0; ++curPathInfoIndex;
		}
	}


private:
	void RenderNode(int nodeId);

public:
	std::vector< SGNode > nodes;
	std::vector< std::list< int > > sceneGraph;
	std::vector< bool > isDFSVisited;
	int dfsParentNodeId = -1;
	int rootId = -1;
	double mvMatrix[16];

	double rotateSpeed = 0.0;
	double rotateAngle = 0.0;

	// path information
	std::vector< PathInfo > pathInfos;						// loaded path information
	int curPathInfoIndex = -1;								// current dealt path node id

	MatrixStack mStack;
};
#endif