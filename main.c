#include <stdio.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "algorithm.h"
#include "file.h"
#include <time.h>
#define WIDTH 640
#define HEIGHT 480
float bubble[3];
float quick[3];


void draw(void);
void buildAlgorithm(const char *name, float * t, int mode);
void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -10, 10);
  glScalef(1, 1, 0);
  glTranslatef(0, 0, 0);
}

int main(int argc, char *argv[]) {
    char str[] = "text.txt";
    writeRandomFile(str, 1000000);
    buildAlgorithm(str, &quick, 1);
    buildAlgorithm(str, &bubble, 2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Levan Gogohia");

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();

    //k = HEIGHT * q / max

    return 0;
}

void draw(void) {
  glViewport(-400,-300,WIDTH + 250, HEIGHT + 200);
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(0.0f, 0.6f, 0.9f);
  glPushMatrix();

  glBegin(GL_LINES);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(1.0f, 0.0f);
    glVertex2f(0.0f, 0.0f);
    float z = 0.0f;
    //x
    for(int i = 0; i < 10; i++){
        z+=0.3f;
        glVertex2d(z, 0.01f);
        glVertex2d(z, -0.01f);

    }
    //y
    z = 0.0f;
    for(int i = 0; i < 10; i++){
        z+=0.1f;
        glVertex2d(0.01f, z);
        glVertex2d(-0.01f, z);
    }
  glEnd();
  float x = 0.0f;
  float y = 0.0f;

  glBegin(GL_LINE_STRIP);
    for(int i = 0; i < 3; i++){
        y = quick[i];
        glVertex2d(0.0f + x, 0.0f + y);
        x += 0.3f;
    }
  glEnd();

  glBegin(GL_LINE_STRIP);
    x = 0.0f;
    for(int i = 0; i < 2; i++){
        y = bubble[i];
        glVertex2d(0.0f + x, 0.0f + y);
        x+=0.3f;
    }
  glEnd();

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void buildAlgorithm(const char *name, float * t, int mode) {
    int * massive = malloc(1000000*sizeof(int));
    readFile(name,massive,1000000);
    int i = 0 ;
    if(mode == 1) { //qsort
        clock_t time_start = clock();
        quick_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000 = time_spent;
        t[i++] = time_spent;
        printf("quick sort 1000 : %f", time_spent);

        time_start = clock();
        quick_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time10000 = time_spent;
        t[i++] = time_spent;
        printf("quick sort 10000 : %f", time_spent);

        time_start = clock();
        quick_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000000 = time_spent;
        t[i++] = time_spent;
        printf("quick sort 1000000 : %f", time_spent);

    }
    else if(mode == 2) { //qsort
        clock_t time_start = clock();
        bubble_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i++] = time_spent;

        time_start = clock();
        bubble_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i++] = time_spent;

        time_start = clock();
        bubble_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i++] = time_spent;

    }
    free(massive);
    massive = NULL;
}
