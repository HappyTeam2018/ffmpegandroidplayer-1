package com.example.jnitest2.app.erdplayer;

/**
 * Created by Administrator on 2015/9/29.
 */
public class AudioLibUtils {

    public static String AV_CODEC_56_LIB_NAME = "avcodec-56";
    public static String AV_FORMAT_56_LIB_NAME = "avformat-56";
    public static String AV_FILTER_LIB_NAME = "avfilter-5";
    public static String AV_DEVICE_LIB_NAME = "avdevice";
    public static String SWSCALE_LIB_NAME = "swscale-3";
    public static String AV_UTIL_56_LIB_NAME = "avutil-54";
    public static String AV_SWRESAMPLE_1_LIB_NAME = "swresample-1";
    public static String GNUSTL_SHARED_LIB_NAME = "gnustl_shared";
    public static String AUDIO_PLAYER_LIB_NAME = "audioplayer";


    public static void loadAudioLib() {
        System.loadLibrary(GNUSTL_SHARED_LIB_NAME);
        System.loadLibrary(AV_UTIL_56_LIB_NAME);
        System.loadLibrary(AV_SWRESAMPLE_1_LIB_NAME);
        System.loadLibrary(AV_CODEC_56_LIB_NAME);
        System.loadLibrary(AV_FORMAT_56_LIB_NAME);
//        System.loadLibrary(AV_FILTER_LIB_NAME);
//        System.loadLibrary(AV_DEVICE_LIB_NAME);
        System.loadLibrary(SWSCALE_LIB_NAME);
        System.loadLibrary(AUDIO_PLAYER_LIB_NAME);
    }
}
