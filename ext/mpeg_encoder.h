#ifndef _mpeg_encoder_h_
#define _mpeg_encoder_h_

//C++ headers
#include <iostream>
#include <algorithm>
#include <vector>

#ifdef __cplusplus
extern "c"
{
#endif
    //C headers
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <time.h>

    //ffmpeg related headers
    #include "libavcodec/avcodec.h"
    #include "libavutil/mathematics.h"
    #include "libswscale/swscale.h"
#ifdef __cplusplus
}
#endif
 

class RGB24MpegEncoder
{

   private: 
        int _w, _h;
        int _size;
        std::vector<uint8_t*> _frameList;
        const char *_filename;
        int _depth;
     
        AVFrame *allocAVFrame(int, int, int); 

    public:
        RGB24MpegEncoder(int , int);
        RGB24MpegEncoder(uint8_t *, int , int);
        ~RGB24MpegEncoder();
        void addFrame(uint8_t *);
	uint8_t *frameAt(int);
        void setOutputFile(const char *outfile) { _filename = outfile; }
	void encodeMpeg();
	int frameListSize(){ return _frameList.size(); }
	int width() { return _w; }
	int height() { return _h; }
};

#endif //mpeg_encoder_h
