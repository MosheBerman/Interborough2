//
//  main.cpp
//  Interborough2
//
//  Created by Moshe Berman on 5/20/13.
//  Copyright (c) 2013 Moshe Berman. All rights reserved.
//

#include "Interoborough.h"
#include "RectangularPrism.h"

/* Prototypes */
void init();
void display();
void timedLoop(int);

/* World & Camera Transforms */
glm::mat4 perspectiveTransform;
glm::mat4 cameraTransform;

/* A dummy prism */

RectangularPrism *p;

/* As my professor would say: "Mommy main" */

int main(int argc, char * argv[])
{
	
	//  The glut initialization function
	glutInit(&argc, argv);
    
    //  Set up display settings
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GL_DOUBLE);

    //  Configure initial windowing settings
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(800, 600);
	
	glutCreateWindow("Interborough 2");
	
	
    //  Handle screen resizes.
//    glutReshapeFunc(reshape);
    
    //  Register the function that handles rendering each frame
    glutDisplayFunc(display);
    
    //  Register the function that handles key down events
//    glutKeyboardFunc(key);
    
    //Set main loop
	glutTimerFunc( 1000 / kFramerate, timedLoop, 0 );
    
    //  Invoke the main loop
    glutMainLoop();
	
	
	glewInit();
    
	// Do our own thing
	init();

	
    return 0;
}

void init()
{
	
	// Field of view, aspect ratio
	perspectiveTransform = glm::perspective(45.0f, 16.0f/9.0f, 0.1f, 100.0f);
	
	p = new RectangularPrism();
	
}

void display()
{
	
}

void timedLoop(int)
{
	
}