#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <math.h>
#include <string.h>

#define ESCAPE 27

/*windows for car rendering*/
GLint window; 
GLint Xsize = 800;
GLint Ysize = 600;

float i, theta;
GLint day = 1; /*intializing a variable for day and night mode*/

/*Translation, scaling, rotation parameters*/
GLfloat xt = 0.0, yt = 0.0, zt = 0.0, xw = 0.0;
GLfloat xs = 0.5, ys = 0.5, zs = 0.5;
GLfloat xangle = 0.0, yangle = 0.0, zangle = 0.0, angle = 0.0;

/*Lighting and color parameters*/
GLfloat r = 1, g = 0, b = 0;
GLint light = 1;
int count = 1;
int flag1 = 0;// to switch car driving mode
int  aflag = 1; //for the orientation of window
int flag2 = 0;// to switch fog effect
int  wheelflag = 0; 
GLUquadricObj *t;


/* Function to set up transformation and projection matrix*/
GLvoid transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, Width / Height, 0.1, 100.0); 
    glMatrixMode(GL_MODELVIEW);
}

/*Function to initialize OpenGL context state*/
GLvoid InitGL(GLfloat Width, GLfloat Height)
{

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0);         
    transform(Width, Height); 

    // creating a new quadric object for drawing
    t = gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);

    glEnable(GL_LIGHTING); // enabling lighting in openGl context

    glEnable(GL_LIGHT0);

    // defining properties for the light source
    GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat diffuseLight[] = {0.8f, 0.8f, 0.8, 1.0f};
    GLfloat specularLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat position[] = {1.5f, 1.0f, 4.0f, 1.0f};

    // seting up different light properties for light source 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

// initializing varios aspects for the rendering
void init()
{
    glClearColor(0, 0, 0, 0); 
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 900.0, 0.0, 600.0, 50.0, -50.0); 
    glutPostRedisplay();                          
}

/*Function to Draw Car Body*/
GLvoid drawWindowScene()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (count == 1)
        InitGL(Xsize, Ysize);
    if (aflag == 1) /* Initialize our window. */
        glClearColor(1, 1, 1, 1);
    else
        glClearColor(0.1, 0.1, 0.1, 0);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0, 0.0, -3.5);
    glRotatef(xangle, 1.0, 0.0, 0.0);
    glRotatef(yangle, 0.0, 1.0, 0.0);
    glRotatef(zangle, 0.0, 0.0, 1.0);
    glTranslatef(xt, yt, zt);
    glScalef(xs, ys, zs);
    glEnable(GL_COLOR_MATERIAL);

    if (flag2 == 1)
    {
        GLfloat fogcolour[4] = {1.0, 1.0, 1.0, 1.0};

        glFogfv(GL_FOG_COLOR, fogcolour);
        glFogf(GL_FOG_DENSITY, 0.1);
        glFogi(GL_FOG_MODE, GL_EXP);
        glFogf(GL_FOG_START, 3.0);
        glFogf(GL_FOG_END, 100.0);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);
    }
    if (flag2 == 0)
    {
        glDisable(GL_FOG);
    }

    
    // Restoring point size
    glPointSize(200.0);

    glBegin(GL_QUADS); /* OBJECT MODULE*/

    /* top of cube*/
    /************************BODY PART OF CAR****************************************/

    /* **********************Front Body*****************************************/
    glColor3f(r, g, b);
    glVertex3f(0.2, 0.4, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.4, 0.2);

    /* bottom of cube*/
    glVertex3f(0.2, 0.4, 0.6);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* front of cube*/
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.2, 0.4, 0.6);
    glVertex3f(0.2, 0.4, 0.2);
    glVertex3f(0.2, 0.2, 0.2);

    /* back of cube.*/
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.6, 0.2, 0.2);

    /* left of cube*/
    glVertex3f(0.2, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.2, 0.4, 0.6);

    /* Right of cube */
    glVertex3f(0.2, 0.2, 0.2);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.2, 0.4, 0.2);

    glVertex3f(0.7, 0.65, 0.6);
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(1.7, 0.65, 0.2); // top cover
    glVertex3f(1.7, 0.65, 0.6);

    //***************************Back Body******************************
    glColor3f(r, g, b); /* Set The Color To Blue*/
    glVertex3f(1.8, 0.5, 0.6);
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.4, 0.6);

    /* bottom of cube*/
    glVertex3f(2.1, 0.2, 0.6);
    glVertex3f(2.1, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8, 0.2, 0.6);

    /* back of cube.*/
    glVertex3f(2.1, 0.4, 0.6);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.2, 0.2);
    glVertex3f(2.1, 0.2, 0.6);

    /* left of cube*/
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1, 0.2, 0.2);

    /* Right of cube */
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8, 0.5, 0.6);
    glVertex3f(2.1, 0.4, 0.6);
    glVertex3f(2.1, 0.2, 0.6);

    //******************MIDDLE BODY************************************
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8, 0.5, 0.6);

    /* bottom of cube*/
    glVertex3f(0.6, 0.2, 0.6);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.6);

    /* back of cube.*/
    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.6, 0.2, 0.2);
    glVertex3f(1.8, 0.2, 0.2);
    glVertex3f(1.8, 0.5, 0.2);

    //*********************Window Part**********************************
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.63, 0.2);
    glVertex3f(0.75, 0.5, 0.2); // quad front window
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f(1.22, 0.63, 0.2);

    glVertex3f(1.27, 0.63, .2);
    glVertex3f(1.25, 0.5, 0.2); // quad back window
    glVertex3f(1.65, 0.5, 0.2);
    glVertex3f(1.67, 0.63, 0.2);

    glColor3f(r, g, b);
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(0.7, 0.5, .2); // first separation
    glVertex3f(0.75, 0.5, 0.2);
    glVertex3f(0.77, 0.65, 0.2);

    glVertex3f(1.2, 0.65, 0.2);
    glVertex3f(1.2, 0.5, .2); // second separation
    glVertex3f(1.25, 0.5, 0.2);
    glVertex3f(1.27, 0.65, 0.2);

    glVertex3f(1.65, 0.65, 0.2);
    glVertex3f(1.65, 0.5, .2); // 3d separation
    glVertex3f(1.7, 0.5, 0.2);
    glVertex3f(1.7, 0.65, 0.2);

    glVertex3f(0.75, 0.65, 0.2);
    glVertex3f(0.75, 0.63, 0.2); // line strip
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f(1.7, 0.65, 0.2);

    glVertex3f(0.75, 0.65, 0.6);
    glVertex3f(0.75, 0.63, 0.6); // line strip
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f(1.7, 0.65, 0.6);

    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.77, 0.63, 0.6);
    glVertex3f(0.75, 0.5, 0.6); // quad front window
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f(1.22, 0.63, 0.6);

    glVertex3f(1.27, 0.63, .6);
    glVertex3f(1.25, 0.5, 0.6); // quad back window
    glVertex3f(1.65, 0.5, 0.6);
    glVertex3f(1.67, 0.63, 0.6);

    glColor3f(r, g, b);
    glVertex3f(0.7, 0.65, 0.6);
    glVertex3f(0.7, 0.5, .6); // first separation
    glVertex3f(0.75, 0.5, 0.6);
    glVertex3f(0.77, 0.65, 0.6);

    glVertex3f(1.2, 0.65, 0.6);
    glVertex3f(1.2, 0.5, .6); // second separation
    glVertex3f(1.25, 0.5, 0.6);
    glVertex3f(1.27, 0.65, 0.6);

    glVertex3f(1.65, 0.65, 0.6);
    glVertex3f(1.65, 0.5, .6);
    glVertex3f(1.7, 0.5, 0.6);
    glVertex3f(1.7, 0.65, 0.6);
    glEnd();

    //**************************************************************
    glBegin(GL_QUADS);

    /* top of cube*/
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.6, 0.5, 0.2); // quad front window
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f(0.7, 0.65, 0.6);

    glVertex3f(1.7, 0.65, .6);
    glVertex3f(1.7, 0.65, 0.2); // quad back window
    glVertex3f(1.8, 0.5, 0.2);
    glVertex3f(1.8, 0.5, 0.6);

    /******************************Surrounding Environment************************************/
    if (flag1)
    {
        glPushMatrix();
        glTranslatef(xw, 0, 0);
        glColor3f(0, 1, 0);
        glVertex3f(-100, 0.1, -100);
        glVertex3f(-100, 0.1, 0); // a green surroundings
        glVertex3f(100, 0.1, 0);
        glVertex3f(100, 0.1, -100);

        glColor3f(0.7, 0.7, 0.7);
        glVertex3f(-100, 0.1, 0);
        glVertex3f(-100, 0.1, 0.45); // a long road
        glVertex3f(100, 0.1, 0.45);
        glVertex3f(100, 0.1, 0);

        glColor3f(1.0, 0.75, 0.0);
        glVertex3f(-100, 0.1, 0.45); // a median
        glVertex3f(-100, 0.1, 0.55);
        glVertex3f(100, 0.1, 0.55);
        glVertex3f(100, 0.1, 0.45);

        glColor3f(0.7, 0.7, 0.7);
        glVertex3f(-100, 0.1, 0.55);
        glVertex3f(-100, 0.1, 1); // a long road
        glVertex3f(100, 0.1, 1);
        glVertex3f(100, 0.1, 0.55);

        glColor3f(0, 1, 0);
        glVertex3f(-100, 0.1, 1);
        glVertex3f(-100, 0.1, 100); // a green surroundings
        glVertex3f(100, 0.1, 100);
        glVertex3f(100, 0.1, 1);
        glPopMatrix();
    }
    glEnd();

    if (wheelflag)
    {
        glPushMatrix();
        glTranslatef(xw, 0, 0);
        glColor3f(0.5, .2, 0.3);
        glBegin(GL_QUADS);
        for (i = 0; i < 200; i += 0.2)
        {
            glVertex3f(-100 + i, 0, 1);
            glVertex3f(-99.9 + i, 0, 1);
            glVertex3f(-99.9 + i, 0.2, 1);
            glVertex3f(-100 + i, 0.2, 1);
            i += 0.5;
        }
        for (i = 0; i < 200; i += 0.2)
        {
            glVertex3f(-100 + i, 0, 0);
            glVertex3f(-99.9 + i, 0, 0);
            glVertex3f(-99.9 + i, 0.2, 0);
            glVertex3f(-100 + i, 0.2, 0);
            i += 0.5;
        }
        glEnd();
        glPopMatrix();
    }

    glBegin(GL_TRIANGLES); /* start drawing the cube.*/

    /* top of cube*/
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(0.6, 0.5, 0.6);
    glVertex3f(0.7, 0.65, 0.6); // tri front window
    glVertex3f(0.7, 0.5, 0.6);

    glVertex3f(0.6, 0.5, 0.2);
    glVertex3f(0.7, 0.65, 0.2); // tri front window
    glVertex3f(0.7, 0.5, 0.2);

    glVertex3f(1.7, 0.65, 0.2);
    glVertex3f(1.8, 0.5, 0.2); // tri back window
    glVertex3f(1.7, 0.5, 0.2);

    glVertex3f(1.7, 0.65, 0.6);
    glVertex3f(1.8, 0.5, 0.6); // tri back window
    glVertex3f(1.7, 0.5, 0.6);

    glEnd();

    /*<--------------------------IGNITION SYSTEM -------------------------------->*/
    glPushMatrix();
    glColor3f(0.3, 0.3, 0.7);
    glTranslatef(1.65, 0.2, 0.3);
    glRotatef(90.0, 0, 1, 0);
    gluCylinder(t, 0.02, 0.03, .5, 10, 10);
    glPopMatrix();

    /* <------------------------------WHEEL ------------------------------------->*/
    glColor3f(0.7, 0.7, 0.7);
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 360; theta = theta + 40)
    {
        glVertex3f(0.6, 0.2, 0.62);
        glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 360; theta = theta + 40)
    {
        glVertex3f(0.6, 0.2, 0.18);
        glVertex3f(0.6 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 360; theta = theta + 40)
    {
        glVertex3f(1.7, 0.2, 0.18);
        glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.18);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (theta = 0; theta < 360; theta = theta + 40)
    {
        glVertex3f(1.7, 0.2, 0.62);
        glVertex3f(1.7 + (0.08 * (cos(((theta + angle) * 3.14) / 180))), 0.2 + (0.08 * (sin(((theta + angle) * 3.14) / 180))), 0.62);
    }
    glEnd();
    glTranslatef(0.6, 0.2, 0.6);
    glColor3f(0, 0, 0);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(0, 0, -0.4);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(1.1, 0, 0);
    glutSolidTorus(0.025, 0.07, 10, 25);

    glTranslatef(0, 0, 0.4);
    glutSolidTorus(0.025, 0.07, 10, 25);
    glPopMatrix();

    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glutPostRedisplay();
    glutSwapBuffers();
}
// }

/*<----------- Switching key board key for the various action-------------------->*/
void inputFromKeyboard(GLubyte key, GLint x, GLint y)
{
    switch (key)
    {
    case ESCAPE:
        printf("escape pressed. exit.\n");
        glutDestroyWindow(window);
        exit(0);
        break;

    case 'x':
        xangle += 5.0;
        glutPostRedisplay();
        break;

    case 'X':
        xangle -= 5.0;
        glutPostRedisplay();
        break;

    case 'y':
        yangle += 5.0;
        glutPostRedisplay();
        break;

    case 'Y':
        yangle -= 5.0;
        glutPostRedisplay();
        break;

    case 'z':
        zangle += 5.0;
        glutPostRedisplay();
        break;

    case 'Z':
        zangle -= 5.0;
        glutPostRedisplay();
        break;

    case 'u': /* Move up */
        yt += 0.2;
        glutPostRedisplay();
        break;

    case 'U':
        yt -= 0.2; /* Move down */
        glutPostRedisplay();
        break;

    case 'f': /* Move forward */
        zt += 0.2;
        glutPostRedisplay();
        break;

    case 'F':
        zt -= 0.2; /* Move away */
        glutPostRedisplay();
        break;

    default:
        break;
    }
}

/*<--------------------Car Moving Key Function ------------------------>*/
static void carMovingKeyFunc(int Key, int x, int y)
{
    switch (Key)
    {
        // backward  move
    case GLUT_KEY_RIGHT:
        if (!wheelflag)
            xt += 0.2;
        if (wheelflag)
        {
            angle += 5;
            xw += 0.2;
        }
        glutPostRedisplay();
        break;

        // forward move
    case GLUT_KEY_LEFT:
        if (!wheelflag)
            xt -= 0.2;
        if (wheelflag)
        {
            angle += 5;
            xw -= 0.2;
        }
        glutPostRedisplay();
        break;
    }
}

/*<--------------------Main Menu ------------------------------>*/

void mainMenu(int id)
{
    if (id == 1)
    {
        flag1 = 0;
        wheelflag = 0;
        glutPostRedisplay();
    }
}

/*<--------------------Car Driving Mode-------------------------------->*/
void carDrivingMode(int id)
{
    if (id == 2)
    {
        flag1 = 1;
        flag2 = 0;
        wheelflag = 1;
        xangle += 5.0;
        glutPostRedisplay();
    }

    if (id == 3)
    {
        flag1 = 1;
        flag2 = 0;
        wheelflag = 0;
        xangle += 5.0;
        glutPostRedisplay();
    }
}
/*<------------------------defining color menu for the car body------------------------>*/
void carColorMenu(int id)
{
    if (id == 4)
    {
        r = 0.8;
        b = g = 0;
        glutPostRedisplay();
    }
    if (id == 5)
    {
        r = g = 0;
        b = 1;
        glutPostRedisplay();
    }
    if (id == 6)
    {
        b = 0;
        r = g = 1;
        glutPostRedisplay();
    }
}

/*<-----------------------Day And Night Mode-------------------------------->*/
void lightModeMenu(int id)
{

    if (id == 7)
    {
        day = 1;
        aflag = 1;
        glClearColor(1, 1, 1, 1);
        glDisable(GL_FOG);
        glutPostRedisplay();
    }

    if (id == 8)
    {
        aflag = 0;
        day = 0;
        flag2 = 2;
        glClearColor(0.1, 0.1, 0.1, 0);
        GLfloat fogcolour[4] = {0.0, 0.0, 0.0, 1.0};

        glFogfv(GL_FOG_COLOR, fogcolour);
        glFogf(GL_FOG_DENSITY, 0.5);
        glFogi(GL_FOG_MODE, GL_EXP);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);

        glutPostRedisplay();
    }
}

/*<--------------------------Main functinon----------------------------------->*/
int main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(Xsize, Ysize);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("3D CAR Animation");
    glutDisplayFunc(drawWindowScene);
    glutKeyboardFunc(inputFromKeyboard);
    glutSpecialFunc(carMovingKeyFunc);
    InitGL(Xsize, Ysize);

    // option for the menu
    int submenu1 = glutCreateMenu(carColorMenu);
    glutAddMenuEntry("red", 4);
    glutAddMenuEntry("blue", 5);
    glutAddMenuEntry("yellow", 6);

    int submenu2 = glutCreateMenu(lightModeMenu);
    glutAddMenuEntry("daymode", 7);
    glutAddMenuEntry("Night mode", 8);

    int submenu3 = glutCreateMenu(carDrivingMode);
    glutAddMenuEntry("with wheel effect", 2);
    glutAddMenuEntry("without wheel effect", 3);

    glutCreateMenu(mainMenu);
    glutAddMenuEntry("car model mode", 1);
    glutAddSubMenu("car driving mode", submenu3);
    glutAddSubMenu("car colors", submenu1);
    glutAddSubMenu("light Mode", submenu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 1;
}