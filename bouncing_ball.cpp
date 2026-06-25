#include <GL/glut.h>
#include <math.h>

float ballX = 250;      // ball X position
float ballY = 250;      // ball Y position
float speedX = 3.0;     // X speed
float speedY = 2.5;     // Y speed
float radius = 20;      // ball radius

void drawCircle(float x, float y, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159 / 180;
        glVertex2f(x + cos(angle) * r, y + sin(angle) * r);
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw ball (red)
    glColor3f(1.0, 0.0, 0.0);
    drawCircle(ballX, ballY, radius);
    
    glFlush();
}

void update(int value) {
    // Update position
    ballX += speedX;
    ballY += speedY;
    
    // Bounce off walls (window size 500x500)
    if (ballX + radius > 500 || ballX - radius < 0) {
        speedX = -speedX;  // reverse X direction
    }
    if (ballY + radius > 500 || ballY - radius < 0) {
        speedY = -speedY;  // reverse Y direction
    }
    
    glutPostRedisplay();          // redraw
    glutTimerFunc(16, update, 0); // ~60 FPS
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bouncing Ball - Computer Graphics Assignment");
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 500, 0, 500);
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);   // start animation
    glutMainLoop();
    
    return 0;
}
//bounce