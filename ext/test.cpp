//compile with:
//g++ *.cpp -lavcodec -lavformat -lavutil -lavfilter -lswscale -o test

#include "mpeg_encoder.h"

int main()
{
    RGB24MpegEncoder *encoder = new RGB24MpegEncoder(100, 100);

    std::cout << encoder->width() << " " << encoder->heigth() << std::endl;
    delete encoder;
    
    return 0;   
}
