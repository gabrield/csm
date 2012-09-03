//compile with:
//g++ *.cpp -lavcodec -lavformat -lavutil -lavfilter -lswscale -o test

#include "mpeg_encoder.h"

int main()
{
    RGB24MpegEncoder *enc = new RGB24MpegEncoder(640, 480);
    int w, h;
    
    w = enc->width();
    h = enc->height();  
 
    uint8_t *img = (uint8_t*) malloc(sizeof(uint8_t)*w*h*3);
    rand_img(img, w, h, 3);

	enc->setOutputFile("test.mpg");


    std::cout << w << " " << h << std::endl;

    for(int i = 0; i < 190; i++)

    {
        enc->addFrame(img); 
        rand_img(img, w, h, 3);
    }

    std::cout << enc->frameListSize() << std::endl;

    
    //enc->encodeMpeg();

    delete enc;
    free(img);

    return 0;   
}
