#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

//this file (program) includes actual implementation of the functions declared in image.c file. More explanation of each function is done below. 





// Given a filename of a ppm image, reads in the image and
// stores it in the ImagePPM structure. Returns the address of
// the ImagePPM structure if the file can be opened or
// NULL otherwise. 
ImagePPM *readPPM(char *filename)  //reads the file and stores the values in pImagePPM struct, if the file can't be open returns NULL
{
    FILE *fp = fopen(filename, "r");
    if(fp == NULL) {
        return NULL;
    }
    ImagePPM *pImagePPM=malloc(sizeof(ImagePPM)); /*Dynamic memory allocation to create a ImagePPM struct variable, pImagePPM*/

    fscanf(fp, "%s", pImagePPM->magic);
    fscanf(fp, "%d", &pImagePPM->width);
    fscanf(fp, "%d", &pImagePPM->height);
    fscanf(fp, "%d", &pImagePPM->max_value);
    int rows = pImagePPM->height;
    int columns = pImagePPM->width;
    pImagePPM->pixels = malloc(sizeof(Pixel *) * rows);   
    for(int i = 0; i < rows ; i++) {
        pImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<columns; j++) {
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].red);
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].green);
            fscanf(fp, "%d", &pImagePPM->pixels[i][j].blue);
        }
    }
    fclose(fp);
    return pImagePPM;
}




// Writes out a ppm image stored in a ImagePPM structure into
// the specified file. Returns 1 if writing is successful or
// 0 otherwise.
int writePPM(ImagePPM *pImagePPM, char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
    return 0;
    }
    fprintf(fp, "%s\n", pImagePPM->magic);
fprintf(fp,"%d %d\n", pImagePPM->width, pImagePPM->height);
fprintf(fp, "%d\n", pImagePPM->max_value);
int rows = pImagePPM->height;
int columns = pImagePPM->width;
for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
        fprintf(fp, "%d ", pImagePPM->pixels[i][j].red);
        fprintf(fp, "%d ", pImagePPM->pixels[i][j].green);
        fprintf(fp, "%d ", pImagePPM->pixels[i][j].blue);
        fprintf(fp, "\t"); 
    }
    fprintf(fp, "\n");
}
fclose(fp);
return 1;
}



// Rotates a ppm image clockwise by 90 degrees, and returns the new ppm image (qimagePPM).
ImagePPM *rotatePPM(ImagePPM *pImagePPM)
{
    ImagePPM *qImagePPM=malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->height = pImagePPM->width;
    qImagePPM->width = pImagePPM->height;
    qImagePPM->max_value = pImagePPM->max_value;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows ; i++) {
        qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0, m=0; i < rows, m < rows; i++, m++) {                
        for(int j = 0, l = columns-1; j < rows, l >= 0; j++, l--) {            //algorithm used to rotate the picture. idea of transpose. 
             qImagePPM->pixels[i][j] =  pImagePPM->pixels[l][m];
        }
    }

	return qImagePPM;
}




// Flips a ppm image horizontally (from left to right), and returns the new ppm image (qImagePPM).
ImagePPM *flipPPM(ImagePPM *pImagePPM)
{
    ImagePPM *qImagePPM=malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->height = pImagePPM->height;
    qImagePPM->width = pImagePPM->width;
    qImagePPM->max_value = pImagePPM->max_value;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows ; i++) {
        qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0, l = 0; i<rows, l<rows; i++, l++) {
        for(int j = 0, m = columns - 1; j<columns, m>=0; j++, m--) {    //algorithm used 
             qImagePPM->pixels[i][j] =  pImagePPM->pixels[l][m];
        }
    }
    return qImagePPM;

}



// Enlarges a ppm image by doubling its size (both width and height), and returns the new ppm image.
ImagePPM *enlargePPM(ImagePPM *pImagePPM)
{
    ImagePPM *qImagePPM = malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->width = (pImagePPM->width)*2;
    qImagePPM->height = (pImagePPM->height)*2;
    qImagePPM->max_value = pImagePPM->max_value;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows; i++) {
       qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0; i<pImagePPM->height; i++) {
        for(int j = 0; j<pImagePPM->width; j++) {                               
            qImagePPM->pixels[2*i][2*j] = pImagePPM->pixels[i][j];
            qImagePPM->pixels[2*i+1][2*j+1] = pImagePPM->pixels[i][j];                  //algorithm used, quadrupling every pixle
            qImagePPM->pixels[2*i+1][2*j] = pImagePPM->pixels[i][j];
            qImagePPM->pixels[2*i][2*j+1] = pImagePPM->pixels[i][j];
        }
    }


   return qImagePPM;
}


// Shrinks a ppm image by reducing its size (both width and height) into the half, and returns the new qImagPPM image.
ImagePPM *shrinkPPM(ImagePPM *pImagePPM)
{
    ImagePPM *qImagePPM = malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->width = (pImagePPM->width)/2;
    qImagePPM->height = (pImagePPM->height)/2;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows; i++) {
       qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0; i<rows; i++) { 
        for(int j = 0; j<columns; j++) {            //algorthm used, reverse idea of double
            qImagePPM->pixels[i][j].red = round((double)(pImagePPM->pixels[2*i][2*j].red + pImagePPM->pixels[2*i+1][2*j].red + pImagePPM->pixels[2*i][2*j+1].red + pImagePPM->pixels[2*i+1][2*j+1].red)/4.0);
            qImagePPM->pixels[i][j].green = round((double)(pImagePPM->pixels[2*i][2*j].green + pImagePPM->pixels[2*i+1][2*j].green + pImagePPM->pixels[2*i][2*j+1].green + pImagePPM->pixels[2*i+1][2*j+1].green)/4.0);
            qImagePPM->pixels[i][j].blue = round((double)(pImagePPM->pixels[2*i][2*j].blue + pImagePPM->pixels[2*i+1][2*j].blue + pImagePPM->pixels[2*i][2*j+1].blue + pImagePPM->pixels[2*i+1][2*j+1].blue)/4.0);
        }
    }
    
 qImagePPM->max_value = pImagePPM->max_value;

    return qImagePPM;
}



// Inverts each color of a ppm image by subtracting its red/green/blue intensity
// from the maximum-value of the image, and returns the new qimagePPM image.
ImagePPM *invertPPM(ImagePPM *pImagePPM)
{
    ImagePPM *qImagePPM=malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->height = pImagePPM->height;
    qImagePPM->width = pImagePPM->width;
    qImagePPM->max_value = pImagePPM->max_value;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows ; i++) {
        qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    for(int i = 0; i<rows; i++) {
        for(int j = 0; j<columns; j++) {
            qImagePPM->pixels[i][j].red = pImagePPM->max_value - pImagePPM->pixels[i][j].red;
            qImagePPM->pixels[i][j].green = pImagePPM->max_value - pImagePPM->pixels[i][j].green;  //algorithm used, deduction of each sub-element (intenstity) of a pixle by its max value
            qImagePPM->pixels[i][j].blue = pImagePPM->max_value - pImagePPM->pixels[i][j].blue;
    }
}
    return qImagePPM;
}



// Crops a ppm image. The crop window is specified by two corners (r1, c1) and (r2, c2), both inclusive.
ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2)
{
    ImagePPM *qImagePPM=malloc(sizeof(ImagePPM));
    strcpy(qImagePPM->magic, pImagePPM->magic);
    qImagePPM->height = abs(r2-r1) +1;
    qImagePPM->width = abs(c2-c1) + 1;
    qImagePPM->max_value = pImagePPM->max_value;
    int rows = qImagePPM->height;
    int columns = qImagePPM->width;
    // printf("%d %d\n", rows, columns); //remove
    qImagePPM->pixels = malloc(sizeof(Pixel *) * rows);
    for(int i = 0; i < rows ; i++) {
        qImagePPM->pixels[i] = malloc(sizeof(Pixel) * columns);
    }
    int bigRow;
    int smallRow;
    int bigColumn;
    int smallColumn;
    
    if(r2>r1) {
        smallRow = r1;
        bigRow = r2;
    }
    else {
        smallRow = r2;
        bigRow = r1;
    }
    // printf(" bigrow= %d smallrow = %d\n", bigRow, smallRow); //remove
    if (c2>c1) {
        smallColumn = c1;
        bigColumn = c2;
    }
    else {
        smallColumn = c2;
        bigColumn = c1;
    }
    // printf("bigcolumn = %d smallcolumn = %d\n", bigColumn, smallColumn); //remove
    // printf("%d\n", pImagePPM->pixels[smallRow][smallColumn].red); //remove
    for(int i = 0, l = smallRow; i<rows, l <= bigRow; i++, l++) {
        for(int j = 0, m = smallColumn; j<columns, m <= bigColumn; j++, m++) {
            qImagePPM->pixels[i][j] =  pImagePPM->pixels[l][m];
            // printf("%d %d\n", l, m); //remove
        }
    }
    // printf("%d\n",  qImagePPM->pixels[0][0].red); //remove
    return qImagePPM;
}


// Frees the space used by a ppm image.
void freeSpacePPM(ImagePPM *pImagePPM)
{
    for (int i = 0; i < pImagePPM->height; i++) {
        free(pImagePPM->pixels[i]);
    }
    free(pImagePPM->pixels);
    free(pImagePPM);
}