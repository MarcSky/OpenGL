#include <stdio.h>
#include <stdlib.h>
#include "GL/gl.h"
#include "GL/glut.h"

void bubble_sort(int *iarr, int num) {
   int i, j, temp;
   for (i = 1; i < num; i++) {
      for (j = 0; j < num - 1; j++) {
         if (iarr[j] > iarr[j + 1]) {
            temp = iarr[j];
            iarr[j] = iarr[j + 1];
            iarr[j + 1] = temp;
         }
      }
   }
}
void draw(void);
int comp (const int *i, const int *j) { return *i - *j; }
int writeRandomFile(const char * name, int count);

int main(int argc, char *argv[])
{

    char str[] = "text.txt";
    writeRandomFile(str, 100);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Levan Gogohia");
    glutDisplayFunc(draw);
    //glutReshapeFunc(Reshape);
    glutMainLoop();

    int a[10] = {1,3,4,5,2,3,4,5,6,7};

//    bubble_sort(a,10);
    //qsort(a, 10, sizeof (int), (int(*) (const void *, const void *)) comp);

    int i ;
    for(i = 0; i <10; i++ ) printf("%d ", a[i]);

    return 0;
}

void draw(void) {
    glClearColor(0,1,0,1);
    glClear(GL_COLOR_BUFFER_BIT );
    glFlush();
}

int writeRandomFile(const char * name, int count) {
    FILE *fd = fopen(name, "w+");
    if(fd) {
        int i;
        for(i = 0; i < count; i++) { fprintf(fd, "%d\n", rand()%100+1); }
        fclose(fd);
        return 1;
    }
    return 0;
}
