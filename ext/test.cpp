//compile with:
//g++ *.cpp -lavcodec -lavformat -lavutil -lavfilter -lswscale -o test

#include "mpeg_encoder.h"


void rand_img(unsigned char *img_ptr, int w, int h, int d)
{
    int i, size;
  
    if (img_ptr == NULL)
        return;

    srand(time(NULL));
  
    size = w * h * d;

    for (i = 0; i < size; i += 3) 
    {
        img_ptr[i]   = rand() % 255; 
        img_ptr[i+1] = rand() % 255; 
        img_ptr[i+2] = rand() % 255; 
    }
    return;
}

int main()
{
    RGB24MpegEncoder *enc = new RGB24MpegEncoder(640, 480);
    int w, h;
    
    w = enc->width();
    h = enc->height();  
 
    unsigned char *img = (unsigned char*) malloc(sizeof(unsigned char)*w*h*3);
    rand_img(img, w, h, 3);

    enc->addFrame(img); 
    enc->addFrame(img); 
    enc->addFrame(img); 

    std::cout << w << " " << h << std::endl;
    std::cout << enc->frameListSize() << std::endl;

    delete enc;
    free(img);

    return 0;   
}
