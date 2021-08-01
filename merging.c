#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Chris Mendoza
Assignment 1
CSC 357
*/

typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int LONG;
    typedef struct tagBITMAPFILEHEADER
    {
        WORD bfType;  //specifies the file type
        DWORD bfSize;  //specifies the size in bytes of the bitmap file
        WORD bfReserved1;  //reserved; must be 0
        WORD bfReserved2;  //reserved; must be 0
        DWORD bfOffBits;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
    }tagBITMAPFILEHEADER;

    typedef struct tagBITMAPINFOHEADER
    {
        DWORD biSize;  //specifies the number of bytes required by the struct
        LONG biWidth;  //specifies width in pixels
        LONG biHeight;  //species height in pixels
        WORD biPlanes; //specifies the number of color planes, must be 1
        WORD biBitCount; //specifies the number of bit per pixel
        DWORD biCompression;//spcifies the type of compression
        DWORD biSizeImage;  //size of image in bytes
        LONG biXPelsPerMeter;  //number of pixels per meter in x axis
        LONG biYPelsPerMeter;  //number of pixels per meter in y axis
        DWORD biClrUsed;  //number of colors used by the bitmap
        DWORD biClrImportant;  //number of colors that are important
    }tagBITMAPINFOHEADER;

    typedef struct pixelColor{
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    }pixelColor;

struct tagBITMAPFILEHEADER readFileHeader(struct tagBITMAPFILEHEADER fileHeader, FILE *fp);
struct tagBITMAPINFOHEADER readInfoHeader(struct tagBITMAPINFOHEADER infoHeader, FILE *fp);
unsigned char* getPixelData(struct tagBITMAPFILEHEADER fileHeader, struct tagBITMAPINFOHEADER infoHeader, FILE *fps);
unsigned char* getRGB(unsigned char* pixData, int rgb, struct tagBITMAPINFOHEADER infoHeader,int x,int y);
unsigned char* getLinear(unsigned char* pixData2, int rgb, struct tagBITMAPINFOHEADER infoHeader,
struct tagBITMAPINFOHEADER infoHeader2, int x,int y);

// try reading file and info seperate and return them so we dont  lose  data
int main(int argc, char *argv[]){
    // for(int i = 1;i < argc;i++){
    //     printf("%s\n",argv[i]);
    // }
    printf("1");
    char sampleText[] = "Expected Input:\n[programname][imagefile1][imagefile2][ratio][outputfile]\n";
    tagBITMAPFILEHEADER fileHeader;
    tagBITMAPINFOHEADER infoHeader;
    tagBITMAPFILEHEADER fileHeader2;
    tagBITMAPINFOHEADER infoHeader2;
    int newWidth;
    //unsigned char outFileHeader[14];
    //unsigned char outInfoHeader[40];
    unsigned char* pixData;
    unsigned char* pixData2;
    pixelColor t;
    if(argc < 5 || argc > 5){
        printf("%s",sampleText);
        return 0;
    }

    FILE *fp = fopen(argv[1],"rb");
    if (fp == NULL){
        printf("\nError cannot read file 1");
        return 1;
    }

    FILE *fp2 = fopen(argv[2],"rb");
    if (fp == NULL){
        printf("\nError cannot read file 2");
        return 1;
    }
    
    // call functions with fp
    fileHeader = readFileHeader(fileHeader,fp);
    infoHeader = readInfoHeader(infoHeader,fp);

    fileHeader2 = readFileHeader(fileHeader2,fp2);
    infoHeader2 = readInfoHeader(infoHeader2,fp2);

    if(fileHeader.bfType!=19778 || fileHeader2.bfType!=19778){
        printf("Error wrong file input");
        return 0;
    }

    printf("2");

    FILE *ef = fopen(argv[4],"wb");
    if(infoHeader.biWidth >= infoHeader2.biWidth){
        fwrite(&(fileHeader.bfType),sizeof(fileHeader.bfType),1,ef);
        fwrite(&(fileHeader.bfSize),sizeof(fileHeader.bfSize),1,ef);
        fwrite(&(fileHeader.bfReserved1),sizeof(fileHeader.bfReserved1),1,ef);
        fwrite(&(fileHeader.bfReserved2),sizeof(fileHeader.bfReserved2),1,ef);
        fwrite(&(fileHeader.bfOffBits),sizeof(fileHeader.bfOffBits),1,ef);

        fwrite(&(infoHeader.biSize),sizeof(infoHeader.biSize),1,ef);
        fwrite(&(infoHeader.biWidth),sizeof(infoHeader.biWidth),1,ef);
        fwrite(&(infoHeader.biHeight),sizeof(infoHeader.biHeight),1,ef);
        fwrite(&(infoHeader.biPlanes),sizeof(infoHeader.biPlanes),1,ef);
        fwrite(&(infoHeader.biBitCount),sizeof(infoHeader.biBitCount),1,ef);
        fwrite(&(infoHeader.biCompression),sizeof(infoHeader.biCompression),1,ef);
        fwrite(&(infoHeader.biSizeImage),sizeof(infoHeader.biSizeImage),1,ef);
        fwrite(&(infoHeader.biXPelsPerMeter),sizeof(infoHeader.biXPelsPerMeter),1,ef);
        fwrite(&(infoHeader.biYPelsPerMeter),sizeof(infoHeader.biYPelsPerMeter),1,ef);
        fwrite(&(infoHeader.biClrUsed),sizeof(infoHeader.biClrUsed),1,ef);
        fwrite(&(infoHeader.biClrImportant),sizeof(infoHeader.biClrImportant),1,ef);
    }

    else{

        fwrite(&(fileHeader2.bfType),sizeof(fileHeader2.bfType),1,ef);
        fwrite(&(fileHeader2.bfSize),sizeof(fileHeader2.bfSize),1,ef);
        fwrite(&(fileHeader2.bfReserved1),sizeof(fileHeader2.bfReserved1),1,ef);
        fwrite(&(fileHeader2.bfReserved2),sizeof(fileHeader2.bfReserved2),1,ef);
        fwrite(&(fileHeader2.bfOffBits),sizeof(fileHeader2.bfOffBits),1,ef);

        fwrite(&(infoHeader2.biSize),sizeof(infoHeader2.biSize),1,ef);
        fwrite(&(infoHeader2.biWidth),sizeof(infoHeader2.biWidth),1,ef);
        fwrite(&(infoHeader2.biHeight),sizeof(infoHeader2.biHeight),1,ef);
        fwrite(&(infoHeader2.biPlanes),sizeof(infoHeader2.biPlanes),1,ef);
        fwrite(&(infoHeader2.biBitCount),sizeof(infoHeader2.biBitCount),1,ef);
        fwrite(&(infoHeader2.biCompression),sizeof(infoHeader2.biCompression),1,ef);
        fwrite(&(infoHeader2.biSizeImage),sizeof(infoHeader2.biSizeImage),1,ef);
        fwrite(&(infoHeader2.biXPelsPerMeter),sizeof(infoHeader2.biXPelsPerMeter),1,ef);
        fwrite(&(infoHeader2.biYPelsPerMeter),sizeof(infoHeader2.biYPelsPerMeter),1,ef);
        fwrite(&(infoHeader2.biClrUsed),sizeof(infoHeader2.biClrUsed),1,ef);
        fwrite(&(infoHeader2.biClrImportant),sizeof(infoHeader2.biClrImportant),1,ef);

    }

    pixData = getPixelData(fileHeader,infoHeader,fp);
    pixData2 = getPixelData(fileHeader2,infoHeader2,fp2);

    double ratio = strtod(argv[3],NULL);
    if(ratio == 0 ||ratio < 0 || ratio > 1){
        printf("Enter ratio between 0 - 1");
        return 0;
    }
    //
    if(infoHeader.biSizeImage < infoHeader2.biSizeImage){
        for(int h = 0; h < infoHeader2.biHeight; h++){
            // each row  height
            float ySmall = h * ((float)(infoHeader2.biHeight/(float)(infoHeader.biHeight)));
            for(int w = 0; w < infoHeader2.biWidth; w+=1){
                float xSmall = w * ((float)(infoHeader2.biWidth/(float)(infoHeader.biWidth)));
                unsigned char blue1 = getRGB(pixData, 3, infoHeader, w, h);
                unsigned char blue2 = getLinear(pixData2, 3, infoHeader, infoHeader2, w, h);
                unsigned char blueres = (blue1 * ratio) + (blue2 * (1-ratio));
                fwrite(&blueres, sizeof(unsigned char), 1, ef);

                unsigned char green1 = getRGB(pixData, 2, infoHeader, w, h);
                unsigned char green2 = getLinear(pixData2, 2, infoHeader, infoHeader2, w, h);
                unsigned char greenres = (green1 * ratio) + (green2 * (1-ratio));
                fwrite(&greenres, sizeof(unsigned char), 1, ef);

                unsigned char red1 = getRGB(pixData, 1, infoHeader, w, h);
                unsigned char red2 = getLinear(pixData2, 1, infoHeader, infoHeader2, w, h);
                unsigned char redres = (red1 * ratio) + red2 * (1-ratio);
                fwrite(&redres, sizeof(unsigned char), 1, ef);
                
                // loopover y then x(w)
                //printf("f");
               
            }
            unsigned char po = 0x00;
            fwrite(&po, sizeof(unsigned char), (infoHeader2.biWidth%4),ef);
        }
    }

    //else if(ratio)
    //printf("adsf");
    //printf("%s", argv[3]);
    if(infoHeader.biWidth >= infoHeader2.biWidth){
        for(int k = 0; k < infoHeader.biSizeImage;k+=3){
            pixData[k] = pixData[k] * ratio + pixData2[k] * (1-ratio);
            pixData[k+1] = pixData[k+1] * ratio + pixData2[k+1] * (1-ratio);
            pixData[k+2] = pixData[k+2] * ratio + pixData2[k+2] * (1-ratio);
        }
        fwrite(pixData,infoHeader.biSizeImage,1,ef);
    }
    // else{
    //    for(int k = 0; k < infoHeader2.biSizeImage;k+=3){
    //         pixData2[k] = pixData[k] * ratio + pixData2[k] * (1-ratio);
    //         pixData2[k+1] = pixData[k+1] * ratio + pixData2[k+1] * (1-ratio);
    //         pixData2[k+2] = pixData[k+2] * ratio + pixData2[k+2] * (1-ratio);
    //     } 
        
    
    // fwrite(pixData,infoHeader.biSizeImage,1,ef);
    //for(int j = 0; j < infoHeader.biSizeImage; j+=3){
        // for(int j = 0; j < 1 * infoHeader.biHeight; j+=3){
            
 
    
    

    //fwrite(pixData,infoHeader.biSizeImage,1,ef);
    //*data = char[size];
    return 0;
    //  loop through array of  pixels  representing each pixel

}
//make a getrgblinear func
unsigned char* getLinear(unsigned char* pixData2, int rgb, struct tagBITMAPINFOHEADER infoHeader,
struct tagBITMAPINFOHEADER infoHeader2, int x,int y ){
    float xsmall = x * ((float)(infoHeader2.biWidth/(float)(infoHeader.biWidth)));
    float ysmall = y * ((float)(infoHeader2.biHeight/(float)(infoHeader.biHeight)));
    int x1 = (int)xsmall;
    int y1 = (int)ysmall;
    int x2 = x1 + 1;
    int y2 = y1 + 1;
    float dx = x - x1;
    float dy = y - y1;
    if(rgb == 1){
    unsigned char red_left_upper = getRGB(pixData2, rgb, infoHeader2, x1, y2);
    unsigned char red_right_upper = getRGB(pixData2, rgb, infoHeader2, x2, y2);
    unsigned char red_left_lower = getRGB(pixData2, rgb, infoHeader2, x1, y1);
    unsigned char red_right_lower = getRGB(pixData2, rgb, infoHeader2, x2, y1);
    unsigned char red_left = red_left_upper * (1-dy) + red_left_lower * dy;
    unsigned char red_right = red_right_upper * (1-dy) + red_right_lower * dy;
    unsigned char red_result = red_left * (1-dx) + red_right * dx;
    return red_result;
    }
    if(rgb == 2){
    unsigned char green_left_upper = getRGB(pixData2, rgb, infoHeader2, x1, y2);
    unsigned char green_right_upper = getRGB(pixData2, rgb, infoHeader2, x2, y2);
    unsigned char green_left_lower = getRGB(pixData2, rgb, infoHeader2, x1, y1);
    unsigned char green_right_lower = getRGB(pixData2, rgb, infoHeader2, x2, y1);
    unsigned char green_left = green_left_upper * (1-dy) + green_left_lower * dy;
    unsigned char green_right = green_right_upper * (1-dy) + green_right_lower * dy;
    unsigned char green_result = green_left * (1-dx) + green_right * dx;
    return green_result;
    }
    //blue
    if(rgb == 3){
    unsigned char blue_left_upper = getRGB(pixData2, rgb, infoHeader2, x1, y2);
    unsigned char blue_right_upper = getRGB(pixData2, rgb, infoHeader2, x2, y2);
    unsigned char blue_left_lower = getRGB(pixData2, rgb, infoHeader2, x1, y1);
    unsigned char blue_right_lower = getRGB(pixData2, rgb, infoHeader2, x2, y1);
    unsigned char blue_left = blue_left_upper * (1-dy) + blue_left_lower * dy;
    unsigned char blue_right = blue_right_upper * (1-dy) + blue_right_lower * dy;
    unsigned char blue_result = blue_left * (1-dx) + blue_right * dx; 
    return blue_result;
    }
}
unsigned char* getRGB(unsigned char* pixData, int rgb, struct tagBITMAPINFOHEADER infoHeader,int x,int y)
{

    int width = infoHeader.biWidth;

    int padding = width%4;
    unsigned char* newpixel = pixData[(width*y)*3+(x*3)+rgb-1 + y * (padding)];
    return newpixel;
}

struct tagBITMAPFILEHEADER readFileHeader(struct tagBITMAPFILEHEADER fileHeader, FILE *fp){

    fread(&(fileHeader.bfType),sizeof(char)*2,1,fp);
    fread(&(fileHeader.bfSize),sizeof(char)*4,1,fp);
    fread(&(fileHeader.bfReserved1),sizeof(char)*2,1,fp);
    fread(&(fileHeader.bfReserved2),sizeof(char)*2,1,fp);
    fread(&(fileHeader.bfOffBits),sizeof(char)*4,1,fp);
    return fileHeader;
    
}

struct tagBITMAPINFOHEADER readInfoHeader(struct tagBITMAPINFOHEADER infoHead, FILE *fps){

    fread(&(infoHead.biSize),sizeof(char)*4,1,fps);
    fread(&(infoHead.biWidth),sizeof(char)*4,1,fps);
    fread(&(infoHead.biHeight),sizeof(char)*4,1,fps);
    fread(&(infoHead.biPlanes),sizeof(char)*2,1,fps);
    fread(&(infoHead.biBitCount),sizeof(char)*2,1,fps);
    fread(&(infoHead.biCompression),sizeof(char)*4,1,fps);
    fread(&(infoHead.biSizeImage),sizeof(char)*4,1,fps);
    fread(&(infoHead.biXPelsPerMeter),sizeof(char)*4,1,fps);
    fread(&(infoHead.biYPelsPerMeter),sizeof(char)*4,1,fps);
    fread(&(infoHead.biClrUsed),sizeof(char)*4,1,fps);
    fread(&(infoHead.biClrImportant),sizeof(char)*4,1,fps);
    return infoHead;
}

unsigned char* getPixelData(struct tagBITMAPFILEHEADER fileHeader, struct tagBITMAPINFOHEADER infoHeader, FILE *fp){
    unsigned char* fileImage;
    fseek(fp, fileHeader.bfOffBits,SEEK_SET);
    fileImage = (unsigned char*)malloc(infoHeader.biSizeImage);
    fread(fileImage,sizeof(unsigned char),infoHeader.biSizeImage,fp);

    // for(int i = 0; i < infoHeader.biSizeImage; i+= 3){

        
    // }
    return fileImage;
}