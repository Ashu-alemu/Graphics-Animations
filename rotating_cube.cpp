#include <GL/glut.h>

float angleX = 0.0;   // rotation angle around X-axis
float angleY = 0.0;   // rotation angle around Y-axis
float angleZ = 0.0;   // rotation angle around Z-axis

void drawCube() {
    glBegin(GL_QUADS);
    
    // Front face (red)
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    
    // Back face (green)
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    
    // Top face (blue)
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    
    // Bottom face (yellow)
    glColor3f(1.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    
    // Right face (magenta)
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0,  1.0);
    glVertex3f( 1.0, -1.0,  1.0);
    
    // Left face (cyan)
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    // Move camera back to see the cube
    glTranslatef(0.0, 0.0, -5.0);
    
    // Rotate cube on all three axes
    glRotatef(angleX, 1.0, 0.0, 0.0);
    glRotatef(angleY, 0.0, 1.0, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);
    
    drawCube();
    
    glutSwapBuffers();
}

void update(int value) {
    // Rotate smoothly on all axes
    angleX += 1.0;
    angleY += 1.2;
    angleZ += 0.8;
    
    // Keep angles within range
    if (angleX > 360) angleX -= 360;
    if (angleY > 360) angleY -= 360;
    if (angleZ > 360) angleZ -= 360;
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // ~60 FPS
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // black background
    glEnable(GL_DEPTH_TEST);            // enable depth testing for 3D
    
    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Rotating Cube - Computer Graphics Assignment");
    
    init();  // initialize 3D settings
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    
    return 0;
}
//cubr