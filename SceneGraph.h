/*
This is a simple scene graph used to render hierarchical scene
The scene graph is represented by a adjacent linked table
*/

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <iostream>
#include "SimpleModel.h"
#include "MatrixStack.h"
#include <vector>
#include <list>


#define OUTPUT_EACH_FRAME

static void MatrixMultiplication(const double m1[16],const double m2[16], double result[16])
{
	double m3[16] = { 0 };
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			double sum = 0.0;
			for (int jj = 0; jj < 4; jj++)
			{
				sum += m1[i * 4 + jj] * m2[jj * 4 + j];
			}
			m3[i * 4 + j] = sum;
		}
	}
	for (int i = 0; i < 16; ++i) result[i] = m3[i];
}


// a node of scene graph
class SGNode
{
public:
	SGNode() { 
		for (int i = 0; i < 16; ++i) {
			mvMatrix[i] = (i % 5 == 0) ? 1 : 0;
			inMatrix[i] = (i % 5 == 0) ? 1 : 0;
		}
	}

	SGNode(std::string fileName) : SGNode() { 
		m.LoadMesh(fileName);
	}

	SGNode(const SGNode &node) {
		m = node.m;
		memcpy(mvMatrix, node.mvMatrix, sizeof(double) * 16);
		memcpy(inMatrix, node.inMatrix, sizeof(double) * 16);
	}
	~SGNode() { }

	void leftUpdate() {
		MatrixMultiplication(mvMatrix, inMatrix, mvMatrix);
	}

	void rightUpdate() {
		MatrixMultiplication(inMatrix, mvMatrix, mvMatrix);
	}

	void storeMVMatrix() {
		memcpy(inMatrix, mvMatrix, sizeof(double) * 16);
	}

public:
	SimpleModel m;			// model
	Vector3D center;		// pivot center
	double mvMatrix[16];		// rener matrix;
	double inMatrix[16];
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
// 		if(verify == 1)
// 			rotateAngle = pathInfos[curPathInfoIndex].angle;
// 		else {
// 			rotateAngle = 0;
// 			++curPathInfoIndex;
// 			verify = 1;
// 		}
// 		verify = -1;
// 		return;

		if (rotateAngle < pathInfos[curPathInfoIndex].angle)
			rotateAngle += rotateSpeed;
		else if (rotateAngle > pathInfos[curPathInfoIndex].angle)
			rotateAngle = pathInfos[curPathInfoIndex].angle;
		else
		{
			// 完成该path的角度，存储该矩阵并进入下一个path
			//nodes[pathInfos[curPathInfoIndex].centerNodeId / 2 * 2].storeMVMatrix();
			if (pathInfos[curPathInfoIndex].centerNodeId % 2 == 1)
				nodes[pathInfos[curPathInfoIndex].centerNodeId].storeMVMatrix();
			else nodes[pathInfos[curPathInfoIndex].rotateNodeId].storeMVMatrix();
			
			std::cout << curPathInfoIndex << " -> ";
			rotateAngle = 0; ++curPathInfoIndex;
		}
	}


private:
	void RenderNode(int nodeId);
	void OutputModels(SimpleModel &m);

public:
	std::vector< SGNode > nodes;
	std::vector< std::list< int > > sceneGraph;
	std::vector< bool > isDFSVisited;
	int dfsParentNodeId = -1;
	int rootId = -1;
	double mvMatrix[16];

	double rotateSpeed = 0.0;
	double rotateAngle = 0.0;
	bool is_output_frame = false;
	// path information
	std::vector< PathInfo > pathInfos;						// loaded path information
	int curPathInfoIndex = -1;								// current dealt path node id

	MatrixStack mStack;

	int renderCnt = 0;
	int faceBase = 1;
	int verify = 1;
};
#endif