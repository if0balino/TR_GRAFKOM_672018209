#include <iostream>
#include <GL/freeglut.h>
#include <math.h>





void display();
void ukuran(int, int);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char, int, int);


float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;
int is_depth;



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "KLIK KIRI" << " = anda menekan LEFT_BUTTON" << std::endl;
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;

    }

    else
        mouseDown = false;

    //else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
    //    std::cout << "KLIK KANAN" << " = anda menekan tombol " << GLUT_RIGHT_BUTTON << std::endl;
    //}
    display();
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glLoadIdentity();
        gluLookAt(0.0f, 0.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); //mengatur penglihatan objek
        glRotatef(xrot, 1.0, 0.0, 0.0);
        glRotatef(yrot, 0.0, 1.0, 0.0);

        glutPostRedisplay();
    }
}



void keyboard(unsigned char key, int x, int y) {

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << key << " = anda menekan tombol " << key << std::endl;

    switch (key)
    {
    case 'z': //zoom +
    case 'Z':
        glTranslatef(0.0, 0.0, 3.0);
        break;
    case 'x': //zoom -
    case 'X':
        glTranslatef(0.0, 0.0, -3.0);
        break;

    case 'w': //geser atas
    case 'W':
        glTranslatef(0.0, 3.0, 0.0);
        break;
    case 'd': //geser kanan
    case 'D':
        glTranslatef(3.0, 0.0, 0.0);
        break;
    case 's': //geser bawah
    case 'S':
        glTranslatef(0.0, -3.0, 0.0);
        break;
    case 'a': //geser kiri
    case 'A':
        glTranslatef(-3.0, 0.0, 0.0);
        break;

    case '0': //rotasi kekanan
        glRotatef(2.0, 0.0, 1.0, 0.0);
        break;
    case '9': //rotasi kekiri
        glRotatef(-2.0, 0.0, 1.0, 0.0);
        break;
    case '1': //putar kekiri
        glRotatef(2.0, 0.0, 0.0, 1.0);
        break;
    case '3': //putar kekanan
        glRotatef(-2.0, 0.0, 0.0, 1.0);
        break;
    case '2': //rotasi kedepan
        glRotatef(2.0, 1.0, 0.0, 0.0);
        break;
    case '4': //rotasi kebelakang
        glRotatef(-2.0, 1.0, 0.0, 0.0);
        break;
    case '5':
        if (is_depth) {
            is_depth = 0;
            glDisable(GL_DEPTH_TEST);
        }
        else {
            is_depth = 1;
            glEnable(GL_DEPTH_TEST);
        }
    }
    display();

}



void display() {

    if (is_depth)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT);


    /*
    CODE HERE
    */
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    /*
    CODE HERE
    */


    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
}



void idle() {
    if (!mouseDown) {
        xrot += 0.3f;
        yrot += 0.4f;
    }

    glutPostRedisplay();
}



void ukuran(int lebar, int tinggi) {
    if (tinggi == 0)
        tinggi = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(55.0, lebar / tinggi, 50.0, 500.0);
    glTranslatef(-5.0, -5.0, -150.0);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //single atau double buffer unutk menampilkan window | warna rgb
    glutInitWindowSize(640, 480); //size, 640px x 480px
    glutInitWindowPosition(500, 20); //posisi windows
    glutCreateWindow("TR_GRAFKOM_672018209");

    //inisialisasi glut
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    //glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHT2);
    glPointSize(5);
    glLineWidth(4);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    is_depth = 1;
    glLoadIdentity(); // dihitung dengan matrix identitas
    //gluOrtho2D(0.0, 640.0, 0.0, 480.0); // untuk memberikan sistem koordinat kepada windows yang kita buat

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(ukuran);
    glutIdleFunc(display);
    glutMainLoop();
    return 0;
}


