//
// Created by Administrator on 2015/10/16.
//

#ifndef ERDPLAYER_DEMO_DEVELOP_FFMPEGDECODER_H
#define ERDPLAYER_DEMO_DEVELOP_FFMPEGDECODER_H

#endif //ERDPLAYER_DEMO_DEVELOP_FFMPEGDECODER_H
#include <string.h>
#include <jni.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/libavcodec/avcodec.h"
#include "../include/libavformat/avformat.h"
#include "../include/libswresample/swresample.h"
#include "../include/libavutil/opt.h"
#include "../include/libavformat/avio.h"

#ifdef __cplusplus
}
#endif

#define FILENAME_MAXLEN 1024
#define null NULL

void openFile(JNIEnv * env,jstring filename);
jint getDataSize();
jbyteArray stream(JNIEnv * env, int minbufsize);
jint getSampleRate();
jint getChannle();
int audioResampling(AVCodecContext *audio_dec_ctx, AVFrame *pAudioDecodeFrame,
                    int out_sample_fmt, int out_channels, int out_sample_rate, char *out_buf);
void JNIInit();
void JNIExit();
int readFrame(AVFormatContext *s, AVPacket *pkt);