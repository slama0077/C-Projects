#ifndef _IMAGE_H_
#define _IMAGE_H_
/*this header file contains struct declaration that's suitable for reading the data set of a picture converted into readable txt file. The file contains different information of the 
picture  such as height, width, max pixel values, and pixels. A picture is just made up of small pixels. Each pixel has three sub-elements which represents 3 fundamental
colors: red, blue, and green. And these sub-elements have their own intensity which makes up a pixel of the picture. 
*/




typedef struct _pixel {  //struct suitable to read and work on pixel
    int red;
    int green;
    int blue;
} Pixel;

typedef struct _imagePPM {
	char magic[3];  // magic identifier, "P3" for PPM
    int width;      // number of columns
    int height;     // number of rows
    int max_value;  // maximum intenrsity of RGB components
    Pixel **pixels; // the actual color pixel data
} ImagePPM;

//these are a few functions we will be working on in this project. More explanations about each function is made in image.c program.



ImagePPM *readPPM(char *filename);

int writePPM(ImagePPM *pImagePPM, char *filename);


ImagePPM *rotatePPM(ImagePPM *pImagePPM);


ImagePPM *flipPPM(ImagePPM *pImagePPM);


ImagePPM *enlargePPM(ImagePPM *pImagePPM);


ImagePPM *shrinkPPM(ImagePPM *pImagePPM);


ImagePPM *invertPPM(ImagePPM *pImagePPM);


ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2);


void freeSpacePPM(ImagePPM *pImagePPM);

#endif