#include <math.h>
#include "model.h"
#include "callbacks.h"
#include "move.h"

void moveItem(World *world)
{
	if (abs((int)(camera.position.x - world->gun.position.x)) < 70 && abs((int)(camera.position.z - world->gun.position.z)) < 70 && camera.position.y < 200)
	{
		double angle = degree_to_radian(camera.pose.z);
		double angle2 = degree_to_radian(camera.pose.z + 130);

		world->gun.position.x = camera.position.x - sin(angle) * 22 - sin(angle2) * -30;
		world->gun.position.y = camera.position.y - 20;
		world->gun.position.z = camera.position.z - cos(angle) * 22 - cos(angle2) * -30;
		//printf("%lf\n", camera.pose.x);
		//world->gun.angle.x = -camera.pose.x;
		world->gun.angle.y = fmod((270 + camera.pose.z), 360);


	}
}