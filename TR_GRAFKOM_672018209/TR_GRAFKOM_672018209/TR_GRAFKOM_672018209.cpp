#include <iostream>
#include <GL/freeglut.h>
#include <math.h>
#include "Kapal.h"





void display();
void ukuran(int, int);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char, int, int);


float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
float pos = 0.0f;
bool mouseDown = false;
int is_depth;


void initcahaya(void)
{
    GLfloat mat_ambient[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_diffuse[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat mat_specular[] = { 0.0, 1.0, 0.0, 0.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 0.0, 1.0, 0.0 };


    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

}



void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        std::cout << "KLIK KIRI" << " = anda menekan LEFT_BUTTON" << std::endl;
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;

    }

    else
        mouseDown = false;
    display();
}

void mouseMotion(int x, int y) {
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;

        glLoadIdentity();
        gluLookAt(0.0f, 40.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); //mengatur penglihatan objek
        glRotatef(xrot, 1.0, 0.0, 0.0);
        glRotatef(yrot, 0.0, 1.0, 0.0);

        glutPostRedisplay();
    }
}



void keyboard(unsigned char key, int x, int y) {
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

    case 'w': //rotasi kebelakang
    case 'W':
        glRotatef(-2.0, 1.0, 0.0, 0.0);
        break;
    case 'd': //rotasi kekanan
    case 'D':
        glRotatef(2.0, 0.0, 1.0, 0.0);
        break;
    case 's': //rotasi kedepan
    case 'S':
        glRotatef(2.0, 1.0, 0.0, 0.0);
        break;
    case 'a': //rotasi kiri
    case 'A':
        glRotatef(-2.0, 0.0, 1.0, 0.0);
        break;
    case 'n': //putar kekiri
    case 'N':
        glRotatef(2.0, 0.0, 0.0, 1.0);
        break;
    case 'm':
    case 'M': //putar kekanan
        glRotatef(-2.0, 0.0, 0.0, 1.0);
        break;
    case 'p':
    case 'P':
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


void onSpecialKeyPressed(int key, int x, int y) {
    std::cout << key << " = anda menekan tombol " << key << std::endl;
    switch (key) {
    case GLUT_KEY_UP:
        glTranslatef(0.0, 3.0, 0.0);
        break;
    case GLUT_KEY_DOWN:
        glTranslatef(0.0, -3.0, 0.0);
        break;
    case GLUT_KEY_LEFT:
        glTranslatef(-3.0, 0.0, 0.0);
        break;
    case GLUT_KEY_RIGHT:
        glTranslatef(3.0, 0.0, 0.0);
        break;
    }
    display();
}




void display() {
    
    if (is_depth)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    else
        glClear(GL_COLOR_BUFFER_BIT);
    

    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glEnd();
    atasdepan(211, 236, 237);
    badancerobong(211, 236, 237);
    bawah(153, 251, 255);
    body(232, 252, 252);
    item(169, 198, 199);
    kolam(33, 174, 255);
    lantaidepan(255, 247, 156);
    lantai(255, 191, 191);
    lekungan(153, 251, 255);
    samping(33, 174, 255);
    sirine(255, 97, 242);
    tiang(232, 252, 252);
    ujungcerobong(232, 252, 252);
    laut(10, 0, 97);
    Pelampung(245, 245, 66);
    cerobong(156, 134, 93);


    glPushMatrix();
    glPopMatrix();
    glutSwapBuffers();
    glTranslatef(-0.003, 0.0, 0.0);
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
    glutInitWindowSize(720, 540); //size, 640px x 480px
    glutInitWindowPosition(200, 20); //posisi windows
    glutCreateWindow("TR_GRAFKOM_672018209");

    //inisialisasi glut
    glClearColor(1.0, 0.73, 0.27, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPointSize(20);
    glLineWidth(4);
    glMatrixMode(GL_MODELVIEW);
    is_depth = 1;
    glLoadIdentity(); // dihitung dengan matrix identitas
    //gluOrtho2D(0.0, 640.0, 0.0, 480.0); // untuk memberikan sistem koordinat kepada windows yang kita buat
    gluLookAt(0.0f, 40.0f, 100.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    initcahaya();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(onSpecialKeyPressed);
    glutReshapeFunc(ukuran);
    glutIdleFunc(display);
    glutMainLoop();

    return 0;
}


