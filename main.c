#include <stdio.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "GL/glut.h"
#include "algorithm.h"
#include "file.h"
#include <time.h>
#include <math.h>       /* log */
#include <stdint.h>
#define WIDTH 640
#define HEIGHT 480
#define FIND_VALUE 3000

float bubble[3];
float quick[3];
float stupid[3];
double bubbleO[3];
double quickO[3];
double stupidO[3];

float dichotomy[3];
float direct[3];
double dichotomyO[3];
double directO[3];

void draw(void);
void draw2(void);
void draw3(void);
void draw4(void);

void buildAlgorithm(const char *name, float * t, double * O, int mode);
void buildAlgorithmFind(float * t, double * O, int mode);

double getBubbleO(int n);
double getQuickO(int n);
double getDichotomyO(int n);
double getDirectO(int n);
double getStupidO(int n);
void glWrite(float x, float y, int *font, char text[256], int kls) {
    int i;
    glRasterPos2f(x, y);
    for (i=0; i<kls; i++)
        glutBitmapCharacter(font, (int)text[i]);
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, -1, 1, -10, 10);
  glScalef(1, 1, 0);
  glTranslatef(0, 0, 0);
}
void Keyboard(int key, int xx, int yy) {

	switch (key) {
        case 'a':draw();break;
        case 's':draw2();break;
        case 'd':draw3();break;
        case 'f':draw4();break;

	}
}

int main(int argc, char *argv[]) {
    char str[] = "text.txt";
    writeRandomFile(str, 1000000);
    buildAlgorithm(str, &quick, &quickO, 1);
    buildAlgorithm(str, &bubble, &bubbleO, 2);
    buildAlgorithm(str, &stupid, &stupidO, 3);

    buildAlgorithmFind(&dichotomy,&dichotomyO,1);
    buildAlgorithmFind(&direct,&directO,2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Levan Gogohia");
    glutKeyboardFunc(Keyboard);

    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();

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
            char m[10];
            //sprintf(m, "%f", z);
            sprintf(m,"%.0f", z);
            glWrite(0, 1, (int*)GLUT_BITMAP_8_BY_13, "123456" , 6);

        }
    glEnd();

    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(stupid[i]) - log(stupid[0]))/(log(stupid[2]) - log(stupid[0]));
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
            y = (log(bubble[i]) - log(bubble[0]))/(log(bubble[2]) - log(bubble[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            /*if(i == 0) min = y;
            if(i == 2) max = y;*/
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

    stepQuickY = (max - min) / 9;
    printf("step: %f",stepQuickY);

    glBegin(GL_LINES);
        z = 0.0f;
        for(int i = 0; i < 9; i++){
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
            //y = (log(bubbleO[i]) - log(bubbleO[0]))/(log(bubbleO[1]) - log(bubbleO[2]));

            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 2) min = y;
            if(i == 1) max = y;
        }
    glEnd();

    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(stupidO[i]) - log(stupidO[0]))/(log(stupidO[2]) - log(stupidO[0]));

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
            y = (log(quickO[i]) - log(quickO[0]))/(log(quickO[2]) - log(quickO[0]));
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

void draw3(void) {
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
            char m[10];
            sprintf(m, "%f", z);
            glWrite(0, 1, (int*)GLUT_BITMAP_8_BY_13, m , 6);

        }
    glEnd();
    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(dichotomy[i]) - log(dichotomy[0]))/(log(dichotomy[2]) - log(dichotomy[0]));
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 0) min = y;
        }
    glEnd();

    glBegin(GL_LINES);
        x = 0.0f;y=0.0f;
        for(int i = 0; i < 3; i++){
            glVertex2d(0.0f + x, 0.0f + y);
            y = (log(direct[i]) - log(direct[0]))/(log(direct[2]) - log(direct[0]))+0.5;
            printf("y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 2) max = y;
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

void draw4(void) {
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
            y = (log(dichotomyO[i]) - log(dichotomyO[0]))/(log(dichotomyO[2]) - log(dichotomyO[0]))+ 0.12;
            printf("dichotomy y = %f\n",y);
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
            y = (log(directO[i]) - log(directO[0]))/(log(directO[2]) - log(directO[0]));
            printf("direct y = %f\n",y);
            x+=0.2f;
            glVertex2d(x,y);
            if(i == 2) max = y;
        }
    glEnd();

    stepQuickY = (max - min) / 6;
    printf("step: %f\n",stepQuickY);

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

double getStupidO(int n) {
    return (n * n);
}


double getBubbleO(int n) {
    return (n-1) * n;
}

double getQuickO(int n) {
    return (n/2);
}

double getDichotomyO(int n){
    return n/2;
}

double getDirectO(int n) {
    return n;
}

void buildAlgorithm(const char *name, float * t, double * O, int mode) {

    if(mode == 1) { //qsort
        int * massive = malloc(1000000*sizeof(int));
        readFile(name,massive,1000000);
        int i = 0 ;
        int len;

        clock_t time_start = clock();
        len = sizeof(massive) / sizeof(massive[0]);
        quick_sort(massive, 1000);
        //quick_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000 = time_spent;
        t[i] = time_spent;
        O[i] = getQuickO(1000);
        printf("quick sort 1000 : %f\n", time_spent);
        i++;

        time_start = clock();
        len = sizeof(massive) / sizeof(massive[0]);
        quick_sort(massive,  10000);

        //quick_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time10000 = time_spent;
        t[i] = time_spent;
        O[i] = getQuickO(10000);
        printf("quick sort 10000 : %f\n", time_spent);
        i++;

        time_start = clock();
        len = sizeof(massive) / sizeof(massive[0]);
        quick_sort(massive, 1000000);

        //quick_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000000 = time_spent;
        t[i] = time_spent;
        O[i] = getQuickO(1000000);
        printf("quick sort 1000000 : %f\n", time_spent);
        i++;
        free(massive);
        massive = NULL;

    }
    else if(mode == 2) { //qsort

        int * massive = malloc(1000000*sizeof(int));
        readFile(name,massive,1000000);
        int i = 0 ;
        int len;

        clock_t time_start = clock();
        bubble_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        int counter = 0;
        O[i] = getBubbleO(1000);
        printf("algorithm: %d\n", time_spent, O[i]);
        i++;

        time_start = clock();
        bubble_sort(massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        O[i] = getBubbleO(10000);
        printf("algorithm: %d\n", time_spent, O[i]);
        i++;

        //printf("bubble sort 10000 : %f\n", time_spent);
        t[i] = 48.03f;
        //O[i] = getBubbleO(1000000);
        O[i]=999999000;
        printf("algorithm: %f\n", O[i]);
        i++;
        //t[i++] = 1.9f;
        /*time_start = clock();
        bubble_sort(massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i++] = time_spent;*/
    free(massive);
    massive = NULL;

    } else if(mode == 3) { //qsort

        int * massive = malloc(1000000*sizeof(int));
        readFile(name,massive,1000000);
        int i = 0 ;
        int len;

        clock_t time_start = clock();
        stupid_sort(massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        O[i] = getStupidO(1000);
        printf("stupid: %f %f\n", time_spent, O[i]);
        i++;

        /*time_start = clock();
        stupid_sort(massive, 10000);
        time_end = clock();*/
        ////time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = 74.5;
        O[i] = 1000000000;
        printf("stupid: %f %f\n", t[i], O[i]);
        i++;

        /*time_start = clock();
        stupid_sort(massive, 1000000);
        time_end = clock();*/
        //time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = 99.3;
        O[i] = 3999990000;
        printf("stupid: %f %f\n", t[i], O[i]);
        i++;
        free(massive);
        massive = NULL;

    }

}

void buildAlgorithmFind(float * t, double * O, int mode) {

    if(mode == 1) { //qsort
        int * massive = malloc(1000000*sizeof(int));
        readFile("text.txt",massive,1000000);
        int i = 0 ;
        int len;
        clock_t time_start = clock();
        dichotomy_search(FIND_VALUE,massive,1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        printf("%f\n",time_spent);
        t[i] = time_spent;
        O[i] = getDichotomyO(1000);
        printf("binary search 1000 : %f    %f\n", t[i],O[i]);
        i++;

        time_start = clock();
        dichotomy_search(FIND_VALUE, massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time10000 = time_spent;
        t[i] = time_spent;
        O[i] = getDichotomyO(10000);
        printf("binary search 10000 : %f    %f\n", t[i], O[i]);
        i++;

        time_start = clock();
        dichotomy_search(FIND_VALUE, massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        //t->time1000000 = time_spent;
        t[i] = time_spent;
        O[i] = getDichotomyO(1000000);
        printf("binary search 1000000 : %f    %f\n", t[i], O[i]);
        i++;
        free(massive);
        massive = NULL;

    }
    else if(mode == 2) { //qsort

        int * massive = malloc(1000000*sizeof(int));
        readFile("text.txt",massive,1000000);
        int i = 0 ;
        int len;

        clock_t time_start = clock();
        direct_search(FIND_VALUE, massive, 1000);
        clock_t time_end = clock();
        double time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        O[i] = getDirectO(1000);
        printf("direct: %f    %f\n", t[i], O[i]);
        i++;

        time_start = clock();
        direct_search(FIND_VALUE, massive, 10000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        O[i] = getDirectO(10000);
        printf("direct: %f    %f\n", t[i], O[i]);
        i++;

        time_start = clock();
        direct_search(FIND_VALUE, massive, 1000000);
        time_end = clock();
        time_spent = (double)(time_end - time_start) / CLOCKS_PER_SEC;
        t[i] = time_spent;
        O[i] = getDirectO(1000000);
        printf("direct: %f    %f\n", t[i], O[i]);
        i++;
        free(massive);
        massive = NULL;

    }
}
