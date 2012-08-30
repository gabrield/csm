#include "mpeg_encoder.h"


AVFrame *RGB24MpegEncoder::allocAVFrame(int pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size((PixelFormat)pix_fmt, width, height);
    printf("size == %d\n", size);
    picture_buf = (uint8_t*)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                (PixelFormat)pix_fmt, width, height);

    return picture;
}


void RGB24MpegEncoder::addFrame(uint8_t *frame_ptr)
{
    uint8_t *frame = new uint8_t[ _w * _h * _depth];
    
    memcpy((void*)frame, (const void*)frame_ptr, _size*sizeof(uint8_t));
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
        // il faut copier le code dans le t_ffmpeg.c ici, c'est le code qui fara l'encodage
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
        delete _frameList[i];
}

