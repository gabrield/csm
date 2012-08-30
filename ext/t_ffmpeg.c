/*
 * Copyright (c) 2001 Fabrice Bellard
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef HAVE_AV_CONFIG_H
#undef HAVE_AV_CONFIG_H
#endif

#include "libavcodec/avcodec.h"
#include "libavutil/mathematics.h"
#include "libswscale/swscale.h"

#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096
static int sws_flags = SWS_BICUBIC;

static AVFrame *alloc_frame(int pix_fmt, int width, int height)
{
    AVFrame *picture;
    uint8_t *picture_buf;
    int size;

    picture = avcodec_alloc_frame();
    if (!picture)
        return NULL;
    size = avpicture_get_size(pix_fmt, width, height);
    printf("size == %d\n", size);
    picture_buf = (uint8_t*)av_malloc(size);
    if (!picture_buf) {
        av_free(picture);
        return NULL;
    }
    avpicture_fill((AVPicture *)picture, picture_buf,
                   pix_fmt, width, height);
    return picture;
}




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



void save_ppm_24bpp(const char *filename, unsigned char *img_buffer, int w, int h)
{
    FILE *fp = fopen(filename, "w");
    int i, size;

    size = w * h * 3;

    (void)fprintf(fp, "P3\n%d %d\n255\n", w, h);
   
    for(i = 0; i < size; i += 3)
    {
        fprintf(fp, "%d %d %d\n", img_buffer[i], img_buffer[i+1], img_buffer[i+2]);
    }
  
    (void)fclose(fp);
  
    return;
}

/*
 * Video encoding example
 */
static void video_encode_example(const char *filename)
{
    AVCodec *codec;
    AVCodecContext *c= NULL;
    int i, out_size, size, x, y, outbuf_size;
    FILE *f;
    AVFrame *picture;
    AVFrame *rgb_picture;
    uint8_t *outbuf, *p_buf, *picture_buf;

    printf("Video encoding\n");

    /* find the mpeg1 video encoder */
    codec = avcodec_find_encoder(CODEC_ID_MPEG1VIDEO);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }

    c = avcodec_alloc_context();
        /* put sample parameters */
    c->bit_rate = 400000;
    /* resolution must be a multiple of two */
    c->width = 640;
    c->height = 480;
    /* frames per second */
    c->time_base= (AVRational){1,25};
    c->gop_size = 10; /* emit one intra frame every ten frames */
    c->max_b_frames = 1;
    c->pix_fmt = PIX_FMT_YUV420P;

    /* open it */
    if (avcodec_open(c, codec) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }

    f = fopen(filename, "wb");
    if (!f) {
        fprintf(stderr, "could not open %s\n", filename);
    }

    /* alloc image and output buffer */
    outbuf_size = c->width * c->height;
    outbuf = (unsigned char*)av_malloc(outbuf_size);
    size = c->width * c->height;
    p_buf =malloc((size * 3) / 2); /* size for YUV 420 */

        fprintf(stdout, "OBA\n");
    
        fprintf(stdout, "OBA\n");


    //picture = alloc_frame(PIX_FMT_YUV420P, c->width, c->height);
    picture = avcodec_alloc_frame();
    //rgb_picture = alloc_frame(PIX_FMT_RGB24, c->width, c->height);

    picture->data[0] = p_buf;
    picture->data[1] = picture->data[0] + size;
    picture->data[2] = picture->data[1] + size / 4;
    picture->linesize[0] = c->width;
    picture->linesize[1] = c->width / 2;
    picture->linesize[2] = c->width / 2;
    
   
  
    //rgb_picture = alloc_frame(PIX_FMT_RGB24, 640, 480);
    
    static struct SwsContext *img_convert_ctx;
    
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
    
    unsigned char *img = (unsigned char*) malloc(sizeof(unsigned char)*640*480*3);
    rand_img(img, 640, 480, 3);
    save_ppm_24bpp("test.ppm", img, 640, 480);
    
    rgb_picture = alloc_frame(PIX_FMT_RGB24, 640, 480);
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
   
    rgb_picture->data[0] = img;
    rgb_picture->data[1] = NULL;
    rgb_picture->data[2] = NULL;
    rgb_picture->linesize[0] = c->width * 3;
    
    sws_scale(img_convert_ctx, rgb_picture->data, rgb_picture->linesize,
                        0, c->height, picture->data, picture->linesize);



    /* encode 10 second of video */
    for(i=0;i<250;i++) {
        fflush(stdout);
	printf("Encoding...\n");
        /* encode the image */
        out_size = avcodec_encode_video(c, outbuf, outbuf_size, picture);
        printf("encoding frame %3d (size=%5d)\n", i, out_size);
        fwrite(outbuf, 1, out_size, f);
    	rand_img(img, 640, 480, 3);
    }

    /* get the delayed frames */
    for(; out_size; i++) {
        fflush(stdout);

        out_size = avcodec_encode_video(c, outbuf, outbuf_size, NULL);
        printf("write frame %3d (size=%5d)\n", i, out_size);
        fwrite(outbuf, 1, out_size, f);
    }

    /* add sequence end code to have a real mpeg file */
    outbuf[0] = 0x00;
    outbuf[1] = 0x00;
    outbuf[2] = 0x01;
    outbuf[3] = 0xb7;
    fwrite(outbuf, 1, 4, f);
    fclose(f);
    free(picture_buf);
    free(outbuf);
    
    free(img);

    avcodec_close(c);
    av_free(c);
    av_free(picture);
    printf("\n");
}



int main(int argc, char **argv)
{
    const char *filename;
    
    avcodec_register_all();
    av_register_all();
    avfilter_register_all();

    video_encode_example("test.mpg");
     
    return 0;
}
