#include "DIY_Physics.h"
#include "Gizmos.h"
#include "Utilities.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/ext.hpp>

#include "Physics_Framework.h"

#define DEFAULT_SCREENWIDTH 1280
#define DEFAULT_SCREENHEIGHT 720

#define PI 3.14159265359

// ------------------------------------------------
Scene* scene;



DIY_Physics::DIY_Physics()
{

}

DIY_Physics::~DIY_Physics()
{

}

bool DIY_Physics::onCreate(int a_argc, char* a_argv[]) 
{
	// initialise the Gizmos helper class
	Gizmos::create();

	// create a world-space matrix for a camera
	//m_cameraMatrix = glm::inverse( glm::lookAt(glm::vec3(10,10,10),glm::vec3(0,0,0), glm::vec3(0,1,0)) );
	m_cameraMatrix = glm::inverse(glm::lookAt(glm::vec3(0, 0, 100),
		glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)));
	float aspectRatio = DEFAULT_SCREENWIDTH / (float)DEFAULT_SCREENHEIGHT;
	// create a an orthogonal projection matrix.
	float fSize = 50;
	float farPlane = 200;
	m_projectionMatrix = glm::ortho<float>(-fSize*aspectRatio, fSize*
		aspectRatio, -fSize, fSize, 0, farPlane);

	// create a perspective projection matrix with a 90 degree field-of-view and widescreen aspect ratio
	// m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, DEFAULT_SCREENWIDTH/(float)DEFAULT_SCREENHEIGHT, 0.1f, 1000.0f);

	// set the clear colour and enable depth testing and backface culling
	glClearColor(0.25f,0.25f,0.25f,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//-----------------------------------
	Sphere *newSphere;
	scene = new Scene();
	scene->gravity = glm::vec3(0, -10, 0);
	//scene->timeStep = .1f;
	/*newSphere = new Sphere(glm::vec3(-40, 0, 0), PI / 4.0f, 30.0f, 0, 3.0f, 1, glm::vec4(1, 0, 0, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(-40, 0, 0), PI / 3.0f, 30.0f, 0, 3.0f, 1, glm::vec4(0, 1, 0, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(-40, 0, 0), PI / 2.0f, 30.0f, 0, 3.0f, 1, glm::vec4(0, 0, 1, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(-40, 0, 0), 0, 30.0f, 0, 3.0f, 1, glm::vec4(1, 1, 0, 1));
	scene->addActor(newSphere);*/
	newSphere = new Sphere(glm::vec3(-40, 20, 0), glm::vec3(30.0f, 0, 0), 0, 13.0f, 1, glm::vec4(1, 0.5f, 0, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(40, 20, 0), glm::vec3(-30.0f, 0, 0), 0, 13.0f, 1, glm::vec4(1, 0.1f, 0.75, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(-40, -20, 0), glm::vec3(0, 30.0f, 0), 0, 13.0f, 1, glm::vec4(0.25, 0.5f, 0.25, 1));
	scene->addActor(newSphere);
	newSphere = new Sphere(glm::vec3(40, -20, 0), glm::vec3(0, 30.0f, 0), 0, 13.0f, 1, glm::vec4(0, 0.3f, 0.75, 1));
	scene->addActor(newSphere);
	Plane* newPlane = new Plane(glm::vec3(1,0,0), 200.0f);
	scene->addActor(newPlane);
	return true;
}

void DIY_Physics::onUpdate(float a_deltaTime) 
{
	// update our camera matrix using the keyboard/mouse
	Utility::freeMovement( m_cameraMatrix, a_deltaTime, 10 );

	// clear all gizmos from last frame
	Gizmos::clear();
	
	// add an identity matrix gizmo
	Gizmos::addTransform( glm::mat4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1) );

	//// add a 20x20 grid on the XZ-plane
	//for ( int i = 0 ; i < 21 ; ++i )
	//{
	//	Gizmos::addLine( glm::vec3(-10 + i, 0, 10), glm::vec3(-10 + i, 0, -10), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//	
	//	Gizmos::addLine( glm::vec3(10, 0, -10 + i), glm::vec3(-10, 0, -10 + i), 
	//					 i == 10 ? glm::vec4(1,1,1,1) : glm::vec4(0,0,0,1) );
	//}

	scene->update();

	// quit our application when escape is pressed
	if (glfwGetKey(m_window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		quit();
}

void DIY_Physics::onDraw() 
{
	// clear the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// get the view matrix from the world-space camera matrix
	glm::mat4 viewMatrix = glm::inverse( m_cameraMatrix );
	
	// draw the gizmos from this frame
	Gizmos::draw(m_projectionMatrix, viewMatrix);
}

void DIY_Physics::onDestroy()
{
	// clean up anything we created
	Gizmos::destroy();
}

// main that controls the creation/destruction of an application
int main(int argc, char* argv[])
{
	// explicitly control the creation of our application
	Application* app = new DIY_Physics();
	
	if (app->create("AIE - DIY_Physics",DEFAULT_SCREENWIDTH,DEFAULT_SCREENHEIGHT,argc,argv) == true)
		app->run();
		
	// explicitly control the destruction of our application
	delete app;

	return 0;
}