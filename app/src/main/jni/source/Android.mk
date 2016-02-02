LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := avcodec
LOCAL_SRC_FILES := ../prebuild/libavcodec-56.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avutil
LOCAL_SRC_FILES := ../prebuild/libavutil-54.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := avformat
LOCAL_SRC_FILES := ../prebuild/libavformat-56.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swscale
LOCAL_SRC_FILES := ../prebuild/libswscale-3.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := swresample
LOCAL_SRC_FILES := ../prebuild/libswresample-1.so
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/include
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_C_INCLUDES += \
    $(LOCAL_PATH)/../prebuild \
    $(LOCAL_PATH)/../include
LOCAL_LDLIBS := -llog
LOCAL_SRC_FILES := \
    com_example_jnitest2_app_erdplayer_audioplayer_AudioDecoder.cpp \
    ffmpegdecoder.cpp
LOCAL_MODULE := libaudioplayer
LOCAL_SHARED_LIBRARIES := avcodec avutil swresample avformat swscale
include $(BUILD_SHARED_LIBRARY)
