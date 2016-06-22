#ifndef _TRACKBALL_H_
#define  _TRACKBALL_H_

#include <Geometry.h>

class TrackBall
{
public:
	Vector2D last_point_2D;
	Vector3D last_point_3D;
	Vector3D zoom_center;
	Vector3D rotate_center;
	double adjustWidth, adjustHeight;
	int Width, Height;
	double zoomRadius;

public:
	double MVmatrix[16];

public:
	TrackBall();
	TrackBall(int width, int height);
	~TrackBall();

	void init();
	void apply();
	/*void applyLightTransform();*/

	void reAdjustTrackBall(double width, double height);

	void mouseMove(int button, Vector2D v2d);
	void mouseClick(int button, int buttonState, Vector2D v2d, Vector3D v3d);
	void assignRotateCenter(Vector3D rotate_center_);

private:
	void mapToSphere(const Vector2D& v2d, Vector3D& v3d);
	void rotate(const Vector3D& axis, double angle);
	void translate(const Vector3D& shift);
	void scale(const Vector3D& scaleFactor);

	/*void MultipleMatrixVector(double *m, Vector3D &rotate_center);*/
};

#endif