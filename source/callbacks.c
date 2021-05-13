#include <math.h>
#include "callbacks.h"
#include "init.h"
#include "draw.h"
#include "model.h"
#include "move.h"

int isHelpOn = 0;
int isGunMoving = 0;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

void display(void)
{
	double elapsed_time = calc_elapsed_time();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	updateCameraPosition(&camera, elapsed_time);
	drawContent(&world);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLdouble)WINDOW_WIDTH / (GLdouble)WINDOW_HEIGHT, 0.1, 20000.0);
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	setViewPoint(&camera);

	if (isHelpOn)
	{
		GLfloat torchForHelp[] = {0.8, 0.8, 0.8, 0.8};
		glLightfv(GL_LIGHT1, GL_AMBIENT, torchForHelp);

		glLoadIdentity();
		gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

		drawHelp(world.helpTexture);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}

	glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;
	
    set_clear_camera_pose(&camera);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		action.moveForward = TRUE;
		break;
	case 's':
		action.moveBackward = TRUE;
		break;
	case 'a':
		action.moveLeft = TRUE;
		break;
	case 'd':
		action.moveRight = TRUE;
		break;
	case '+':
		action.increaseLight = TRUE;
		break;
	case '-':
		action.decreaseLight = TRUE;
		break;
	case 'e':
		if (!isGunMoving)
		{
			isGunMoving = 1;
			action.moveItem = TRUE;
			break;
		}
		else
		{
			isGunMoving = 0;
			action.moveItem = FALSE;
			break;
		}
	case 'c':
		action.squat = TRUE;
		break;
	case 27:
		exit(0);
	default:
		printf("Unknown input!");
	}

	glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		action.moveForward = FALSE;
		break;
	case 's':
		action.moveBackward = FALSE;
		break;
	case 'a':
		action.moveLeft = FALSE;
		break;
	case 'd':
		action.moveRight = FALSE;
		break;
	case '+':
		action.increaseLight = FALSE;
		break;
	case '-':
		action.decreaseLight = FALSE;
		break;
	case 'c':
		action.squat = FALSE;
		break;
	}
	glutPostRedisplay();
}

void specialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_F1:
		if (isHelpOn == 1)
		{
			isHelpOn = 0;
		}
		else
			isHelpOn = 1;
	}
}

void mouse(int button, int state, int x, int y)
{
	mouse_x = x;
	mouse_y = y;
}

void motion(int x, int y)
{
	double horizontal, vertical;

	horizontal = mouse_x - x;
	vertical = mouse_y - y;

	rotate_camera(&camera, horizontal, vertical);

	mouse_x = x;
	mouse_y = y;

	glutPostRedisplay();
}

void idle()
{
	glutPostRedisplay();
}

double calc_elapsed_time()
{
	static int last_frame_time = 0;
	int current_time;
	double elapsed_time;

	current_time = glutGet(GLUT_ELAPSED_TIME);
	elapsed_time = (double)(current_time - last_frame_time) / 1000.0;
	last_frame_time = current_time;

	return elapsed_time;
}

void updateCameraPosition(struct Camera *camera, double elapsed_time)
{
	float speed = 40;
	double distance;

	distance = elapsed_time * CAMERA_SPEED * speed;

	if (action.moveForward)
	{
		moveCameraForward(camera, distance);
	}

	if (action.moveBackward)
	{
		moveCameraBackward(camera, distance);
	}

	if (action.moveLeft)
	{
		moveCameraLeft(camera, distance);
	}

	if (action.moveRight)
	{
		moveCameraRight(camera, distance);
	}

	if (action.increaseLight)
	{
		if (light_ambient[0] < 1)
			light_ambient[0] = light_ambient[1] = light_ambient[2] += 0.03;
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}

	if (action.decreaseLight)
	{
		if (light_ambient[0] > -0.60)
			light_ambient[0] = light_ambient[1] = light_ambient[2] -= 0.03;
		glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	}
	if (action.moveItem)
	{
		moveItem(&world);
	}
	if (action.squat)
	{
		squat(camera, 1);
	}
	if (!action.squat)
	{
		squat(camera, 0);
	}
}
