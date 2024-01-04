#include "Moderator/Moderator.h"

void init() {
    glClearColor(0.1, 0.1, 0.1, 0.1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0);
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    glutInitWindowPosition(200, 200);
    glutCreateWindow("21120479 - Pham Long Khanh - 21CNTN");
    init();
    Moderator::createMenu();
    glutKeyboardFunc(Moderator::keyboard);
     glutSpecialFunc(Moderator::specialKeyboard);
    glutMouseFunc(Moderator::mouse);
    glutMotionFunc(Moderator::mouseMotion);
    glutDisplayFunc(Moderator::display);

    glutMainLoop();

    return 0;
}