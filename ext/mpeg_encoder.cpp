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

        AVCodec *codec;
        AVCodecContext *c= NULL;
        int i, out_size, size, rgb_buf_size;
        FILE *f;
        AVFrame *picture;
        AVFrame *rgb_picture;
        uint8_t *rgb_buf, *yuv_buf, *picture_buf;

        printf("Video encoding\n");

        avcodec_register_all();
        av_register_all();
        avfilter_register_all();


        /* find the mpeg2 video encoder */
        codec = avcodec_find_encoder(CODEC_ID_MPEG2VIDEO);
        if (!codec) {
            fprintf(stderr, "[1] codec not found\n");
            exit(1);
        }

        c = avcodec_alloc_context();
            /* put sample parameters */
        c->bit_rate = 400000;
        /* resolution must be a multiple of two */
        c->width = _w;
        c->height = _h;
        /* frames per second */
        c->time_base= (AVRational){1,25};
        c->gop_size = 10; /* emit one intra frame every ten frames */
        c->max_b_frames = 1;
        c->pix_fmt = PIX_FMT_YUV420P;

        /* open it */
        if (avcodec_open(c, codec) < 0) {
            fprintf(stderr, "could not open codec\n");
            return;
        }

        f = fopen(_filename, "wb");
        if (!f) {
            fprintf(stderr, "could not open %s\n", _filename);
            return;
        }

        /* alloc image and output buffer */
        rgb_buf_size = c->width * c->height;
        rgb_buf = (uint8_t*)av_malloc(rgb_buf_size);
        //size = c->width * c->height;
        yuv_buf = (uint8_t*)malloc((size * 3) / 2); /* size for YUV 420 */


        //picture = alloc_frame(PIX_FMT_YUV420P, c->width, c->height);
        picture = avcodec_alloc_frame();
        //rgb_picture = alloc_frame(PIX_FMT_RGB24, c->width, c->height);

        picture->data[0] = yuv_buf;
        picture->data[1] = picture->data[0] + rgb_buf_size;
        picture->data[2] = picture->data[1] + rgb_buf_size / 4;
        picture->linesize[0] = c->width;
        picture->linesize[1] = c->width / 2;
        picture->linesize[2] = c->width / 2;
        
       
      
        //rgb_picture = alloc_frame(PIX_FMT_RGB24, 640, 480);
        
        static struct SwsContext *img_convert_ctx;
        static int sws_flags = SWS_BICUBIC;

        if (img_convert_ctx == NULL)
        {
            img_convert_ctx = sws_getContext(c->width, c->height,
                                             PIX_FMT_RGB24,
                                             c->width, c->height,
                                             c->pix_fmt,
                                             sws_flags, NULL, NULL, NULL);
            if (img_convert_ctx == NULL)
            {
                fprintf(stderr, "Cannot initialize the conversion context\n");
                exit(1);
            }
        }
        
        //uint8_t *img = (uint8_t*) malloc(sizeof(uint8_t)*640*480*3);
        //rand_img(img, 640, 480, 3);
        //save_ppm_24bpp("test.ppm", img, 640, 480);
        
        rgb_picture = allocAVFrame(PIX_FMT_RGB24, c->width, c->height);
        /*
         if (!rgb_picture)
            return NULL;
        
        size = avpicture_get_size(PIX_FMT_RGB24, c->width, c->height);
        picture_buf = (uint8_t*)av_malloc(size);
        
        if (!picture_buf) {
            av_free(rgb_picture);
            return NULL;
        }
        avpicture_fill((AVPicture *)rgb_picture, picture_buf,
                       PIX_FMT_RGB24, c->width, c->height);
       */
      
        for(int i = 0; i < _frameList.size(); i++)
        {
	    rgb_picture->data[0] = _frameList[i];
	    rgb_picture->data[1] = NULL;
	    rgb_picture->data[2] = NULL;
	    rgb_picture->linesize[0] = c->width * 3;
	    
	    sws_scale(img_convert_ctx, rgb_picture->data, rgb_picture->linesize,
			0, c->height, picture->data, picture->linesize);



        /* encode 10 second of video */
        //for(i=0;i<250;i++) {
            fflush(stdout);
            printf("Encoding...\n");
            /* encode the image */
            out_size = avcodec_encode_video(c, rgb_buf, rgb_buf_size, picture);
            printf("encoding frame %3d (size=%5d)\n", i, out_size);
            fwrite(rgb_buf, 1, out_size, f);
            //rand_img(img, 640, 480, 3);
        //}
        }
        /* get the delayed frames */
        for(; out_size; i++) {
            fflush(stdout);

            out_size = avcodec_encode_video(c, rgb_buf, rgb_buf_size, NULL);
            printf("write frame %3d (size=%5d)\n", i, out_size);
            fwrite(rgb_buf, 1, out_size, f);
        }

        /* add sequence end code to have a real mpeg file */
        rgb_buf[0] = 0x00;
        rgb_buf[1] = 0x00;
        rgb_buf[2] = 0x01;
        rgb_buf[3] = 0xb7;
        fwrite(rgb_buf, 1, 4, f);
        fclose(f);
        free(picture_buf);
        free(rgb_buf);
        
        //free(img);

        avcodec_close(c);
        av_free(c);
        av_free(picture);
        printf("\n");
    }
    else
    {
        std::cout << "could not write file" << std::endl;
        return;
    }
}

RGB24MpegEncoder::~RGB24MpegEncoder()
{
    for (int i = 0; i < (int)_frameList.size(); i++ )
        delete _frameList[i];
}

