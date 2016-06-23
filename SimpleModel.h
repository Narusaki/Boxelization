#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include <Geometry.h>
#include <vector>
#include <string>

class SimpleModel
{
public:
	SimpleModel();
	SimpleModel(const SimpleModel& m);
	~SimpleModel();

	bool LoadMesh(std::string fileName);
	void Normalize();
	void Normalize(Vector3D center, double scale);
	void Render();
	
private:
	bool LoadOBJ(std::string fileName);
	bool LoadOFF(std::string fileName);

public:
	std::vector< Vector3D > verts;
	std::vector< int > faces;
};
#endif