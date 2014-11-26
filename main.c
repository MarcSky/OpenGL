#include <stdio.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "algorithm.h"
#include "file.h"
#include <time.h>
#include <math.h>       /* log */

#define WIDTH 640
#define HEIGHT 480
float bubble[3];
float quick[3];
float bubbleO[3];
float quickO[3];

void draw(void);
void draw2(void);
void buildAlgorithm(const char *name, float * t, float * O, int mode);
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
    buildAlgorithm(str, &quick, &quickO, 1);
    buildAlgorithm(str, &bubble, &bubbleO, 2);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Levan Gogohia");

    glutDisplayFunc(draw2);
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
    float stepQuickY;
    float min,max;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    glBegin(GL_LINES);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        for(int i = 0; i < 3; i++){
            z+=0.2f;
            glVertex2d(z, 0.01f);
            glVertex2d(z, -0.01f);
        }
    glEnd();
    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(bubble[i]) - log(bubble[0]))/(log(bubble[2]) - log(bubble[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 0) min = y;
            if(i == 2) max = y;
        }
    glEnd();

    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(quick[i]) - log(quick[0]))/(log(quick[2]) - log(quick[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 0) min = y;
        }
    glEnd();

    stepQuickY = (max - min) / 6;
    printf("step: %f",stepQuickY);

    glBegin(GL_LINES);
        z = 0.0f;
        for(int i = 0; i < 6; i++){
            z+=stepQuickY;
            glVertex2d(0.01f, z);
            glVertex2d(-0.01f, z);
        }
    glEnd();


    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}

void draw2(void) {
    glViewport(-400,-300,WIDTH + 250, HEIGHT + 200);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.6f, 0.9f);
    glPushMatrix();
    float stepQuickY;
    float min,max;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    glBegin(GL_LINES);
        glVertex2f(0.0f, 1.0f);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(0.0f, 0.0f);
        for(int i = 0; i < 3; i++){
            z+=0.2f;
            glVertex2d(z, 0.01f);
            glVertex2d(z, -0.01f);
        }
    glEnd();
    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(bubbleO[i]) - log(bubbleO[0]))/(log(bubbleO[2]) - log(bubbleO[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 0) min = y;
            if(i == 2) max = y;
        }
    glEnd();

    /*glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(quick[i]) - log(quick[0]))/(log(quick[2]) - log(quick[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 0) min = y;
        }
    glEnd();
*/
    stepQuickY = (max - min) / 6;
    printf("step: %f",stepQuickY);

    glBegin(GL_LINES);
        z = 0.0f;
        for(int i = 0; i < 6; i++){
            z+=stepQuickY;
            glVertex2d(0.01f, z);
            glVertex2d(-0.01f, z);
        }
    glEnd();


    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}


void buildAlgorithm(const char *name, float * t, float * O, int mode) {
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
        printf("quick sort 1000 : %f\n", time_spent);

        time_start = clock();
        quick_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time10000 = time_spent;
        t[i++] = time_spent;
        printf("quick sort 10000 : %f\n", time_spent);

        time_start = clock();
        quick_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000000 = time_spent;
        t[i++] = time_spent;
        printf("quick sort 1000000 : %f\n", time_spent);

    }
    else if(mode == 2) { //qsort
        clock_t time_start = clock();
        bubble_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        int counter = 0;
        for(int j = 0; j<1000; j++) {
            counter -= j;
        }
        O[i++] = 1000 * (1000-1) + counter;
        printf("bubble sort 1000 : %f\n", time_spent);

        time_start = clock();
        bubble_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        counter = 0;
        for(int j = 0; j<10000; j++) {
            counter -= j;
        }
        O[i++] = 10000 * (10000-1) + counter;

        printf("bubble sort 10000 : %f\n", time_spent);
        t[i] = 48.03f;
        O[i++] = 100000000;
        //t[i++] = 1.9f;
        /*time_start = clock();
        bubble_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i++] = time_spent;*/

    }
    free(massive);
    massive = NULL;
}
