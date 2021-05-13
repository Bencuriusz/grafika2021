#include "camera.h"
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define size 500

double degree_to_radian(double degree)
{
	return degree * M_PI / 180.0;
}

void collisionDetection(struct Camera *camera)
{
	if (camera->position.x > mapSize || camera->position.x < -mapSize || camera->position.z < -mapSize || camera->position.z > mapSize)
		camera->position = camera->prevPosition;
}

void init_camera(struct Camera *camera)
{
	camera->position.x = 0;
	camera->position.y = 100;
	camera->position.z = -150;

	camera->pose.x = 0;
	camera->pose.y = 0;
	camera->pose.z = 0;
}

void setViewPoint(const struct Camera *camera)
{
	glRotatef(-(camera->pose.x), 1.0, 0, 0);
	glRotatef(-(camera->pose.z), 0, 1.0, 0);
	glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(struct Camera *camera, double horizontal, double vertical)
{
	// Vertical
	//camera->pose.x += vertical;

	// Horizontal
	camera->pose.z += horizontal;

	if (camera->pose.z < 0)
	{
		camera->pose.z += 360.0;
	}

	if (camera->pose.z > 360.0)
	{
		camera->pose.z -= 360.0;
	}

	if (camera->pose.x < 0)
	{
		camera->pose.x += 360.0;
	}

	if (camera->pose.x > 360.0)
	{
		camera->pose.x -= 360.0;
	}
}

void set_clear_camera_pose(struct Camera *camera)
{
	camera->pose.x = 0;
}

void moveCameraForward(struct Camera *camera, double distance)
{
	camera->prevPosition = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
	collisionDetection(camera);
}

void moveCameraBackward(struct Camera *camera, double distance)
{
	camera->prevPosition = camera->position;
	double angle = degree_to_radian(camera->pose.z);

	camera->position.z += cos(angle) * distance;
	camera->position.x += sin(angle) * distance;
	collisionDetection(camera);
}

void moveCameraLeft(struct Camera *camera, double distance)
{
	camera->prevPosition = camera->position;
	double angle = degree_to_radian(camera->pose.z + 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
	collisionDetection(camera);
}

void moveCameraRight(struct Camera *camera, double distance)
{
	camera->prevPosition = camera->position;
	double angle = degree_to_radian(camera->pose.z - 90.0);

	camera->position.z -= cos(angle) * distance;
	camera->position.x -= sin(angle) * distance;
	collisionDetection(camera);
}

void squat(struct Camera *camera, int isSquattin)
{
	camera->prevPosition = camera->position;

	if (!isSquattin && camera->position.y <= 100)
	{
		camera->position.y += 15;
		collisionDetection(camera);
	}
	else if(isSquattin && camera->position.y >= 85)
	{
		camera->position.y -= 15;
		collisionDetection(camera);
	}
}
