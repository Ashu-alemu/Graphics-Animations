#include <GL/glut.h>
#include <math.h>

float angle = 0.0;        // rotation angle
float red = 1.0;          // color component for effect

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Move to center of window
    glTranslatef(250, 250, 0);
    
    // Apply rotation
    glRotatef(angle, 0.0, 0.0, 1.0);
    
    // Draw triangle with gradient-like colors
    glBegin(GL_TRIANGLES);
        
        // Vertex 1 (top) - Red
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(0, 120);
        
        // Vertex 2 (bottom left) - Green
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(-100, -80);
        
        // Vertex 3 (bottom right) - Blue
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f(100, -80);
        
    glEnd();
    
    // Optional: Draw outline for better visibility
    glColor3f(1.0, 1.0, 1.0);  // white outline
    glBegin(GL_LINE_LOOP);
        glVertex2f(0, 120);
        glVertex2f(-100, -80);
        glVertex2f(100, -80);
    glEnd();
    
    glFlush();
    glutSwapBuffers();  // for smoother animation if using double buffer
}

void update(int value) {
    // Increase rotation angle
    angle += 2.0;
    
    // Keep angle in range 0-360
    if (angle > 360) {
        angle -= 360;
    }
    
    // Request screen refresh
    glutPostRedisplay();
    
    // Call update again after 16ms (~60 FPS)
    glutTimerFunc(16, update, 0);
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);  // black background
    
    // Set up 2D orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);  // window size 500x500
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Rotating Triangle - Computer Graphics");
    
    init();  // initialize settings
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);  // start animation
    glutMainLoop();
    
    return 0;
}
//rotate2