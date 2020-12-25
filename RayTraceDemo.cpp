#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Scene.h"
#include "Objects.h"
#include "Rays.h"
#include "Camera.h"
#include "Vector3.h"

#include <GL/glut.h>


using namespace std;

int width = 0;
int height = 0;

Scene* world = new Scene();

//Rotation 
float Rot_num = 0.5f;
int number = 1;

class tracescene
{
public:
	void draw(float * pixinfo, float Rot_num, int width, int height, int number)
	{
		Vector3 RotLight(50 + cos(Rot_num) * 50, 100, 5 + 5 * sin(Rot_num));
		world->lights.begin()->position = RotLight;

	
		Vector3 RotBall(0.0f + 3.0f * cos(Rot_num), 2.0f, 12.0f + 3.0f * sin(Rot_num));
		list<Object*>::iterator it = world->objects.begin();
		it++; it++; it++;
		(*it)->position = RotBall;

		
		Vector3 cameraPoint(0.0f, 0.0f, -5.0f + sin(Rot_num) * -5.0f);
		Vector3 left_down_plane(-1.0f, -1.0f, 0.5f);
		Vector3 up_plane(0.0f, 2.0f, 0.0f);
		Vector3 right_plane(2.0f, 0.0f, 0.0f);

		//ViewPlane Color
		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				float wRatio = (float)w / width;
				float hRatio = (float)h / height;
				Vector3 hPoint = left_down_plane + (up_plane * hRatio);
				Vector3 wPoint = left_down_plane + (right_plane * wRatio);

				//Plane Point
				Vector3 plane_point(wPoint.v[0], hPoint.v[1], 0.5f + sin(Rot_num) * -5.0f);

				//Camera(Ray Tracing)
				Ray ray(cameraPoint, plane_point - cameraPoint);
				ray.shoot(world->objects, world->lights, number);

			
				*(pixinfo + h * width * 3 + w * 3 + 0) = ray.color.v[0];
				*(pixinfo + h * width * 3 + w * 3 + 1) = ray.color.v[1];
				*(pixinfo + h * width * 3 + w * 3 + 2) = ray.color.v[2];
				
			}


		}
		return;
	}


}hello;

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float* pixinfo = new float[3 * width * height];
	hello.draw(pixinfo, Rot_num, width, height, number);
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixinfo);
	glFlush();

	delete[] pixinfo;

}

void mouseCB(int button, int state, int x, int y)
{
	

	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			Rot_num +=0.05;
			draw();
			cout << " Counterclockwise Rotation " << endl;
			glutPostRedisplay();

		}
		
	}

	else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			Rot_num -= 0.05;
			draw();
			cout << " Clockwise Rotation " << endl;
			glutPostRedisplay();

		}

	}
}



void setupComponentInsert(void)
{

	Material red;
	red.ambient.set(0.17f, 0.012f, 0.012f);
	red.diffuse.set(0.61f, 0.04f, 0.04f);
	red.specular.set(0.73f, 0.63f, 0.63f);
	red.emittance.set(0.0f, 0.0f, 0.0f);
	red.shininess = 60;
	red.reflection = 0.3f;
	red.transmission = 0.8f;
	red.refractiveIdx = 1.5f;

	Material green;
	green.ambient.set(0.0f, 0.0f, 0.0f);
	green.diffuse.set(0.1f, 0.35f, 0.1f);
	green.specular.set(0.45f, 0.55f, 0.45f);
	green.emittance.set(0.2f, 0.2f, 0.2f);
	green.shininess = 5;
	green.reflection = 0.5f;
	green.shininess = 30;

	Material glass;
	glass.ambient.set(0.0f, 0.0f, 0.0f);
	glass.diffuse.set(0.0f, 0.0f, 0.0f);
	glass.specular.set(0.9f, 0.9f, 0.9f);
	glass.shininess = 60;
	glass.reflection = 0.9f;
	glass.transmission = 0.9f;
	glass.refractiveIdx = 1.0f;

	Material gold;
	gold.ambient.set(0.247f, 0.2f, 0.075f);
	gold.diffuse.set(0.75f, 0.606f, 0.227f);
	gold.specular.set(0.628f, 0.556f, 0.366f);
	gold.shininess = 40;
	gold.reflection = 0.3f;
	gold.transmission = 0.0f;
	gold.refractiveIdx = 0.0f;
	
	Sphere* one = new Sphere(Vector3(-0.3f, 0.0f, 8.0f), 1.0f);
	one->setMaterial(glass);
	world->addObject(one);

	Sphere* two = new Sphere(Vector3(0.0f, 1.5f, 12.0f), 2.0f);
	two->setMaterial(red);
	world->addObject(two);

	Sphere* three = new Sphere(Vector3(1.5f, 0.0f, 9.0f), 0.6f);
	three->setMaterial(green);
	world->addObject(three);
	
	Sphere* four = new Sphere(Vector3(-1.0f, 2.0f, 9.0f), 0.6f);
	four->setMaterial(gold);
	world->addObject(four);

	Plane* plane1 = new Plane(Vector3(0.0f, -2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f), 100.0f, 100.0f);
	Material floor;
	floor.ambient.set(0.05f, 0.05f, 0.05f);
	floor.diffuse.set(0.5f, 0.5f, 0.5f);
	floor.specular.set(0.7f, 0.7f, 0.7f);
	floor.shininess = 8;
	floor.reflection = 0.5f;
	floor.transmission = 0.0f;
	floor.refractiveIdx = 0.0f;
	plane1->setMaterial(floor);
	world->addObject(plane1);


	Light light;
	light.color.set(1.0f, 1.0f, 1.0f);
	light.position.set(100.0f, 100.0f, 5.0f);
	world->addLight(light);

}

void init(void) 
{
	glClearColor(1.0, 1.0, 1.0, 0.0); 
	setupComponentInsert();
}

// Resize
void resize(int w, int h)
{
	width = w;
	height = h;


	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


	glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		cout << "1111111111" << endl;
		exit(0);
		break;
	case '1':
		number = 1;
		draw();
		cout << " number of reflection=1 "<<endl;
		glutPostRedisplay();
		break;
	case '2':
		number = 2;
		draw();
		cout << " number of reflection=2 " << endl;
		glutPostRedisplay();
		break;
	case '3':
		number = 3;
		draw();
		cout << " number of reflection=3 " << endl;
		glutPostRedisplay();
		break;
	case '4':
		number = 4;
		draw();
		cout << " number of reflection=4 " << endl;
		glutPostRedisplay();
		break;
	}
}
int main(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100); 
	glutCreateWindow("raytracing");

	init(); 
     
	glutReshapeFunc(resize);  
	glutDisplayFunc(draw);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouseCB);
	

	glutMainLoop(); 

	return 0;  
}
