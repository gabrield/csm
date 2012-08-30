//compile with:
//g++ *.cpp -lavcodec -lavformat -lavutil -lavfilter -lswscale -o test

#include "mpeg_encoder.h"

int main()
{
    RGB24MpegEncoder encoder(100, 100);

    std::cout << encoder.width() << " " << encoder.heigth() << std::endl;
    
    return 0;   
}
