#ifndef _mpeg_encoder_h_
#define _mpeg_encoder_h_

//C++ headers
#include <iostream>
#include <algorithm>
#include <vector>

#ifdef __cplusplus
extern "C"
{
#endif
    //C headers
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <time.h>

    //ffmpeg related headers
    #include "libavcodec/avcodec.h"
    #include "libavfilter/avfilter.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
#ifdef __cplusplus
}
#endif
 

class RGB24MpegEncoder
{

	private: 
		int _w, _h;
		int _size;
		std::vector<unsigned char*> _frameList;
		const char *_filename;
		int _depth;

		AVCodec *codec;
		AVCodecContext *c;
		int i, out_size, size, x, y, outbuf_size;
		FILE *f;
		AVFrame *picture;
		AVFrame *rgb_picture;
		unsigned char *outbuf, *p_buf, *picture_buf;
		struct SwsContext *img_convert_ctx;
		
		AVFrame *allocAVFrame(int, int, int); 
		void initMpegEncoder();
		void closeAll();

    public:
		RGB24MpegEncoder(int , int);
		RGB24MpegEncoder(uint8_t *, int , int);
		~RGB24MpegEncoder();
		void addFrame(unsigned char *);
		uint8_t *frameAt(int);
		void setOutputFile(const char *outfile) { _filename = outfile; }
		void encodeMpeg();
		int frameListSize(){ return _frameList.size(); }
		int width() { return _w; }
		int height() { return _h; }
};

void rand_img(unsigned char *img_ptr, int w, int h, int d);


#endif //mpeg_encoder_h
