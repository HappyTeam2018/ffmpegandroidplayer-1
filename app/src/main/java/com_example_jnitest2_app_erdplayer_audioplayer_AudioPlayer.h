/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer */

#ifndef _Included_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
#define _Included_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    stream
 * Signature: (I)[B
 */
JNIEXPORT jbyteArray JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_stream
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    getDataSize
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_getDataSize
  (JNIEnv *, jobject);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    openFile
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_openFile
  (JNIEnv *, jobject, jstring);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    getSampleRate
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_getSampleRate
  (JNIEnv *, jobject);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    getChannel
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_getChannel
  (JNIEnv *, jobject);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    JNIInit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_JNIInit
  (JNIEnv *, jobject);

/*
 * Class:     com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer
 * Method:    JNIExit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_jnitest2_app_erdplayer_audioplayer_AudioPlayer_JNIExit
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif