#include <GL/glut.h>

float carX = 0.0;      // car position (starts at left)
float speed = 2.0;     // movement speed

void drawCar(float x, float y) {
    // Car body (rectangle)
    glColor3f(0.0, 0.0, 1.0);  // blue
    glBegin(GL_QUADS);
        glVertex2f(x, y);
        glVertex2f(x + 100, y);
        glVertex2f(x + 100, y + 40);
        glVertex2f(x, y + 40);
    glEnd();
    
    // Car roof
    glColor3f(0.5, 0.5, 0.5);  // gray
    glBegin(GL_QUADS);
        glVertex2f(x + 20, y + 40);
        glVertex2f(x + 80, y + 40);
        glVertex2f(x + 70, y + 70);
        glVertex2f(x + 30, y + 70);
    glEnd();
    
    // Wheel 1 (left)
    glColor3f(0.0, 0.0, 0.0);  // black
    glBegin(GL_QUADS);
        glVertex2f(x + 15, y - 10);
        glVertex2f(x + 35, y - 10);
        glVertex2f(x + 35, y);
        glVertex2f(x + 15, y);
    glEnd();
    
    // Wheel 2 (right)
    glBegin(GL_QUADS);
        glVertex2f(x + 65, y - 10);
        glVertex2f(x + 85, y - 10);
        glVertex2f(x + 85, y);
        glVertex2f(x + 65, y);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw road (gray line at bottom)
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
        glVertex2f(0, 80);
        glVertex2f(500, 80);
        glVertex2f(500, 100);
        glVertex2f(0, 100);
    glEnd();
    
    // Draw car
    drawCar(carX, 80);
    
    glFlush();
    glutSwapBuffers();
}

void update(int value) {
    // Move car to the right
    carX += speed;
    
    // Reset to left side when off screen
    if (carX > 500) {
        carX = -100;
    }
    
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);  // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Moving Car - Computer Graphics Assignment");
    
    glClearColor(0.7, 0.7, 0.7, 0.0);  // light gray background
    gluOrtho2D(0, 800, 0, 600);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    
    return 0;
}
//car