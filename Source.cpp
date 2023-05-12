#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h

// Global variables 
char title[] = "3D Shapes with animation";
GLfloat angle = 0.0f;     // Rotational angle for octahedron
int refreshMills = 15;        // refresh interval in milliseconds

// Initialize OpenGL Graphics 
void initGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClearDepth(1.0f);                   // Set background depth to farthest
    glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
}

// Handler for window-repaint event. Called back when the window first appears and
// whenever the window needs to be re-painted. 

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix

    // Render a octahedron with static shades of grey
    glLoadIdentity();                 // Reset the model-view matrix
    glTranslatef(-0.5f, 1.0f, -7.0f);  // Move right and into the screen
    glRotatef(angle, 0.5f, 1.5f, -0.5f);  // Rotate about (0.5,1.5,-0.5)-axis
    
    glBegin(GL_TRIANGLES);
    //Triangle 1
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);   //V0
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);   //V1
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   //V2
    //Triangle 2
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);   //V0
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   //V2
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);   //V3
    //Triangle 3
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);   //V0
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);   //V3
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);   //V4
    //Triangle 4
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, 1.0f, 0.0f);   //V0
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);   //V4
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);   //V1
    //Triangle 5
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, -3.0f, 0.0f);   //V0'
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);   //V1
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   //V2
    //Triangle 6
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, -3.0f, 0.0f);   //V0'
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);   //V2
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);   //V3
    //Triangle 7
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, -3.0f, 0.0f);   //V0'
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);   //V3
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);   //V4
    //Triangle 8
    glColor3f(1.0f, 1.0f, 1.0f); glVertex3f(0.0f, -3.0f, 0.0f);   //V0'
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);   //V4
    glColor3f(0.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);   //V1

    glEnd();


    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)

    // Update the rotational angle after each refresh
    angle +=1.0f;
}

//  Called back when timer expired
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
}

// Handler for window re-size event. Called back when the window first appears and whenever the window is re-sized with its new width and height 
void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(50.0f, aspect, 0.1f, 100.0f);
}

// Main function: GLUT runs as a console application starting at main()
int main(int argc, char** argv) {
    glutInit(&argc, argv);            // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
    glutInitWindowSize(640, 480);   // Set the window's initial width & height
    glutInitWindowPosition(50, 50); // Position the window's initial top-left corner
    glutCreateWindow(title);          // Create window with the given title
    glutDisplayFunc(display);       // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);       // Register callback handler for window re-size event
    initGL();                       // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);     // First timer call immediately
    glutMainLoop();                 // Enter the infinite event-processing loop
    return 0;
}
