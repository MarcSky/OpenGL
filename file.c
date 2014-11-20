#include "file.h"
void writeRandomFile(const char * name, int count) {
    FILE *fd = fopen(name, "w+");
    if(fd) {
        int i;
        for(i = 0; i < count; i++) { fprintf(fd, "%d\n", rand()%100+1); }
        fclose(fd);
    }
}

void readFile(const char * name, int * massive, int count) {
    FILE *fp = fopen(name, "r");
    if(fp) {
        int i = 0, buffer = 0;
        for (i = 0; i < count; i++) {
            fscanf(fp,"%d",&buffer);
            massive[i] = buffer;
        }
        fclose(fp);
    }
}

