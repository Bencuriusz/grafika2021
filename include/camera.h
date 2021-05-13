
#ifndef CAMERA_H
#define CAMERA_H

#include "model.h"

#define CAMERA_SPEED 5.0

struct Camera
{
	struct Vertex position;
	struct Vertex pose;
	struct Vertex prevPosition;
};


/*
* Converts degree to radian
*/
double degree_to_radian(double degree);

/**
 * Initialize the camera position and direction.
 */
void init_camera(struct Camera* camera);

/**
 * Transform the models into the view point of the camera.
 */
void setViewPoint(const struct Camera* camera);

/**
 * Rotate the camera horizontally and vertically.
 */
void rotate_camera(struct Camera* camera, double horizontal, double vertical);

/**
 * Resets the vertical pose of the camera.
 */
void set_clear_camera_pose(struct Camera* camera);

/**
 * Move the camera forward.
 */
void moveCameraForward(struct Camera* camera, double distance);

/**
 * Move the camera backward.
 */
void moveCameraBackward(struct Camera* camera, double distance);

/**
 * Move the camera left.
 */
void moveCameraLeft(struct Camera* camera, double distance);

/**
 * Move the camera right.
 */
void moveCameraRight(struct Camera* camera, double distance);

/**
 * Move the camera down.
 */
void squat(struct Camera* camera, int isSquattin);

#endif // CAMERA_H

