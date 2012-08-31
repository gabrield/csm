#ifndef mpeg_encoder_h
#define mpeg_encoder_h
//C headers
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//C++ headers
#include <iostream>
#include <algorithm>
#include <vector>


//ffmpeg related headers
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/mathematics.h"
#include "libswscale/swscale.h"
}


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
