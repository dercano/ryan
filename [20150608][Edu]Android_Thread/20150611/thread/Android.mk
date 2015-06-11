
# Android.mk

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := thread4.cpp
LOCAL_SHARED_LIBRARIES := libutils
LOCAL_MODULE := thread

include $(BUILD_EXECUTABLE)
