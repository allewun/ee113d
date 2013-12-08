

// bitmap stuff
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef unsigned int LONG;

typedef struct tagBITMAPFILEHEADER {
    unsigned short bfType;      //specifies the file type
    unsigned int bfSize;        //specifies the size in bytes of the bitmap file
    unsigned short bfReserved1; //reserved; must be 0
    unsigned short bfReserved2; //reserved; must be 0
    unsigned int bOffBits;      //species the offset in bytes from the bitmapfileheader to the bitmap bits
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;         //specifies the number of bytes required by the struct
    LONG biWidth;         //specifies width in pixels
    LONG biHeight;        //species height in pixels
    WORD biPlanes;        //specifies the number of color planes, must be 1
    WORD biBitCount;      //specifies the number of bit per pixel
    DWORD biCompression;  //spcifies the type of compression
    DWORD biSizeImage;    //size of image in bytes
    LONG biXPelsPerMeter; //number of pixels per meter in x axis
    LONG biYPelsPerMeter; //number of pixels per meter in y axis
    DWORD biClrUsed;      //number of colors used by th ebitmap
    DWORD biClrImportant; //number of colors that are important
} BITMAPINFOHEADER;

float* loadBitmapFileGrayscale(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
float* loadGrayBitmapFileGrayscale(char *filename, BITMAPINFOHEADER *bitmapInfoHeader);
