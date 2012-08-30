#include <iostream>
#include <algorithm>
#include <vector>


class RGB24MpegEncoder
{
    
    int _w, _h;
    int _size;
    std::vector<uint8_t*> _frameList;
    const char *_filename;
    int _depth; 

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
	int heigth() { return _h; }
};


void RGB24MpegEncoder::addFrame(uint8_t *frame_ptr)
{
    uint8_t *frame = new uint8_t[ _w * _h * _depth];
    
    memcpy((void*)frame, (const void*)frame_ptr, _size*sizeof(uint8_t *));
    _frameList.push_back(frame);
}

uint8_t *RGB24MpegEncoder::frameAt(int n_frame)
{
    return _frameList.at(n_frame);
}


RGB24MpegEncoder::RGB24MpegEncoder(int w, int h)
{
    _depth = 3;  //RGB24 bits depth
    _w = w;
    _h = h;
    _size = _w * _h * _depth;
}


RGB24MpegEncoder::RGB24MpegEncoder(uint8_t *img_ptr, int w, int h)
{
    _depth = 3;  //RGB24 bits depth
    _w = w;
    _h = h;
    _size = _w * _h * _depth;
   addFrame(img_ptr);
}

void RGB24MpegEncoder::encodeMpeg()
{
    if(_filename != NULL)
    {
        //commence a faire quelque chose
    }
    else
    {
        std::cout << "could not write file" << std::endl;
        return;
    }
}

RGB24MpegEncoder::~RGB24MpegEncoder()
{
    for (int i = 0; i < _frameList.size(); i++ )
        free(_frameList[i]);
}

