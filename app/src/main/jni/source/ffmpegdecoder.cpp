//
// Created by Administrator on 2015/10/16.
//
#include "ffmpegdecoder.h"
#include <android/log.h>

#define TAG "audio_track"
#define TAG1 "timon_audio_track-1"

char fileName[FILENAME_MAXLEN];
JNIEnv *env;
AVFormatContext *pFormatCtx = NULL;
AVCodecContext *pCodecCtx = NULL;
AVCodec *pCodec = NULL;
AVPacket avpkt;
AVFrame *avfrm;
int audioStream;
size_t data_size;
char *arr = NULL;
jbyteArray jarr;
int pktLeft;

void openFile(JNIEnv *env, jstring jfilename) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile");
    strncpy(fileName, env->GetStringUTFChars(jfilename, 0), FILENAME_MAXLEN);
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->0.5");
    int code = avformat_open_input(&pFormatCtx, fileName, NULL, NULL);
    if (code != 0) {
        __android_log_print(ANDROID_LOG_DEBUG, null, "fail to open file");
        char errbuf[100];
        av_strerror(code, errbuf, sizeof(errbuf));
        __android_log_print(ANDROID_LOG_INFO, TAG, "open error:%s", errbuf);
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->0.6");
    if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
        __android_log_print(ANDROID_LOG_DEBUG, null, "fail to open track");
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->0.7");
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->1");
    int i;
    audioStream = -1;
    for (i = 0; i < pFormatCtx->nb_streams; i++) {
        if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
            audioStream = i;
            break;
        }
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->2");
    if (audioStream == -1) {
        __android_log_print(ANDROID_LOG_DEBUG, null, "fail to open track");
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile--->3");
    pCodecCtx = pFormatCtx->streams[audioStream]->codec;
    pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
    if (pCodec == NULL) {
        __android_log_print(ANDROID_LOG_DEBUG, null, "fail to find decoder");
    }
    if (pCodec->capabilities & CODEC_CAP_TRUNCATED)
        pCodecCtx->flags |= CODEC_FLAG_TRUNCATED;

    if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0) {
        __android_log_print(ANDROID_LOG_DEBUG, null, "fail to open decoder");
    }
    __android_log_print(ANDROID_LOG_DEBUG, null, "File opened:\n decoder: %s", pCodec->name);
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "openFile end");
}

jint getDataSize() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "getDataSize");
    return (jint) data_size;
}

jbyteArray stream(JNIEnv *env, jint minbufsize) {
    data_size = 0;
    if (!arr) {
        arr = (char *) malloc(sizeof(char) * minbufsize * 3);
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "sizeof(char) * minbufsize * 2 : %d", sizeof(char) * minbufsize * 2);
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream1");
    while (data_size < minbufsize) {
        //__android_log_print(ANDROID_LOG_DEBUG, null, "reading");
        if (pktLeft <= 0) {
            for (; ;) {
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "avpkt->size1:%d", avpkt.size);
                int len = av_read_frame(pFormatCtx, &avpkt);
                //397565 18432
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "avfrm->size2:%d", avpkt.size);
                char errbuf[100];
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "loop->%d", len);
                av_strerror(len, errbuf, sizeof(errbuf));
                __android_log_print(ANDROID_LOG_INFO, TAG, "loop->error:%s", errbuf);
                if (len < 0) {
                    __android_log_print(ANDROID_LOG_DEBUG, null, "cannot read packet");
                    data_size = 0;
                    free(arr);
                    arr = NULL;
                    return jarr;
                }
                if (avpkt.stream_index != audioStream) {
                    av_free_packet(&avpkt);
                    continue;
                }

                pktLeft = avpkt.size;
                break;
            }
        }
        int got_frame = 0, len;
        len = avcodec_decode_audio4(pCodecCtx, avfrm, &got_frame, &avpkt);
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "avpkt->time->dts:%lld", avpkt.dts);
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "avpkt->time->pts:%lld", avpkt.pts);
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream len-->%d", len);
        //25804800 dts
        //1074563437 pts
        //325955917 duration 255920113
        //10997760
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "pFormatCtx->duration--->%lld", pFormatCtx->duration);
        if (len < 0) {
            av_free_packet(&avpkt);
            break;
        }
        if (got_frame) {
            __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream5");
//            int dsize = av_samples_get_buffer_size(NULL, pCodecCtx->channels,
//                                                   avfrm->nb_samples,
//                                                   pCodecCtx->sample_fmt, 1);
            int resampLen = audioResampling(pCodecCtx, avfrm, AV_SAMPLE_FMT_S16, 2, 44100,
                                            arr + data_size);
            data_size += resampLen;
            pktLeft -= len;
        } else {
            av_free_packet(&avpkt);
            break;
        }
//        }
    }
    jarr = env->NewByteArray(data_size);
    env->SetByteArrayRegion(jarr, 0, data_size, (jbyte *) arr);

    return jarr;
}

jint getSampleRate() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "getSampleRate");
    if (pCodecCtx)
        return (jint)(pCodecCtx->sample_rate);
}

jint getChannle() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "getChannle");
    if (pCodecCtx)
        return (jint)(pCodecCtx->channels);
}

void JNIInit() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "JNIInit");
    av_register_all();
    avcodec_register_all();
    avfrm = av_frame_alloc();
    av_init_packet(&avpkt);
}

void JNIExit() {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "JNIExit");
    av_frame_free(&avfrm);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);
    avformat_free_context(pFormatCtx);
    free(arr);
    arr = NULL;
    pktLeft = 0;
}

int audioResampling(AVCodecContext *audio_dec_ctx, AVFrame *pAudioDecodeFrame,
                    int out_sample_fmt, int out_channels, int out_sample_rate, char *out_buf) {
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream12");
    SwrContext *swr_ctx = NULL;
    int data_size = 0;
    int ret = 0;
    int64_t src_ch_layout = AV_CH_LAYOUT_STEREO; //初始化这样根据不同文件做调整
    int64_t dst_ch_layout = AV_CH_LAYOUT_STEREO; //这里设定ok
    int dst_nb_channels = 0;
    int dst_linesize = 0;
    int src_nb_samples = 0;
    int dst_nb_samples = 0;
    int max_dst_nb_samples = 0;
    uint8_t **dst_data = NULL;
    int resampled_data_size = 0;
    //重新采样
    if (swr_ctx) {
        swr_free(&swr_ctx);
    }
    swr_ctx = swr_alloc();
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream12-1");
    if (!swr_ctx) {
        printf("swr_alloc error \n");
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream13");
        return -1;
    }

    src_ch_layout = (audio_dec_ctx->channel_layout &&
                     audio_dec_ctx->channels ==
                     av_get_channel_layout_nb_channels(audio_dec_ctx->channel_layout)) ?
                    audio_dec_ctx->channel_layout :
                    av_get_default_channel_layout(audio_dec_ctx->channels);
    if (out_channels == 1) {
        dst_ch_layout = AV_CH_LAYOUT_MONO;
    }
    else if (out_channels == 2) {
        dst_ch_layout = AV_CH_LAYOUT_STEREO;
    }
    else {
        //可扩展
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream12-2");
    if (src_ch_layout <= 0) {
        printf("src_ch_layout error \n");
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream14");
        return -1;
    }
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream12-3");
    src_nb_samples = pAudioDecodeFrame->nb_samples;
    if (src_nb_samples <= 0) {
        printf("src_nb_samples error \n");
        __android_log_print(ANDROID_LOG_DEBUG, TAG, "stream15");
        return -1;
    }

    /* set options */
    av_opt_set_int(swr_ctx, "in_channel_layout", src_ch_layout, 0);
    av_opt_set_int(swr_ctx, "in_sample_rate", audio_dec_ctx->sample_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "in_sample_fmt", audio_dec_ctx->sample_fmt, 0);

    av_opt_set_int(swr_ctx, "out_channel_layout", dst_ch_layout, 0);
    av_opt_set_int(swr_ctx, "out_sample_rate", out_sample_rate, 0);
    av_opt_set_sample_fmt(swr_ctx, "out_sample_fmt", (AVSampleFormat) out_sample_fmt, 0);
    swr_init(swr_ctx);
    max_dst_nb_samples = dst_nb_samples =
            av_rescale_rnd(src_nb_samples, out_sample_rate, audio_dec_ctx->sample_rate,
                           AV_ROUND_UP);
    if (max_dst_nb_samples <= 0) {
        printf("av_rescale_rnd error \n");
        return -1;
    }

    dst_nb_channels = av_get_channel_layout_nb_channels(dst_ch_layout);
    ret = av_samples_alloc_array_and_samples(&dst_data, &dst_linesize, dst_nb_channels,
                                             dst_nb_samples, (AVSampleFormat) out_sample_fmt, 0);
    if (ret < 0) {
        printf("av_samples_alloc_array_and_samples error \n");
        return -1;
    }


    dst_nb_samples = av_rescale_rnd(swr_get_delay(swr_ctx, audio_dec_ctx->sample_rate) +
                                    src_nb_samples, out_sample_rate, audio_dec_ctx->sample_rate,
                                    AV_ROUND_UP);
    if (dst_nb_samples <= 0) {
        return -1;
    }
    if (dst_nb_samples > max_dst_nb_samples) {
        av_free(dst_data[0]);
        ret = av_samples_alloc(dst_data, &dst_linesize, dst_nb_channels,
                               dst_nb_samples, (AVSampleFormat) out_sample_fmt, 1);
        max_dst_nb_samples = dst_nb_samples;
    }
    data_size = av_samples_get_buffer_size(NULL, audio_dec_ctx->channels,
                                           pAudioDecodeFrame->nb_samples,
                                           audio_dec_ctx->sample_fmt, 1);
    if (data_size <= 0) {
        return -1;
    }
    resampled_data_size = data_size;
    if (swr_ctx) {
        ret = swr_convert(swr_ctx, dst_data, dst_nb_samples,
                          (const uint8_t **) pAudioDecodeFrame->data,
                          pAudioDecodeFrame->nb_samples);
        if (ret <= 0) {
            return -1;
        }

        resampled_data_size = av_samples_get_buffer_size(&dst_linesize, dst_nb_channels,
                                                         ret, (AVSampleFormat) out_sample_fmt, 1);
        if (resampled_data_size <= 0) {
            return -1;
        }
    }
    else {
        return -1;
    }
    //将值返回去
    memcpy(out_buf, dst_data[0], resampled_data_size);
    if (dst_data) {
        av_freep(&dst_data[0]);
    }
    av_freep(&dst_data);
    dst_data = NULL;

    if (swr_ctx) {
        swr_free(&swr_ctx);
    }
    return resampled_data_size;
}