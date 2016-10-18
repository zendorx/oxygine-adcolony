LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE    := oxygine-adcolony_static
LOCAL_MODULE_FILENAME := oxygine-adcolony

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/../oxygine-framework/oxygine/src/ \
		src/ \
		src/android \
					

LOCAL_SRC_FILES := \
		src/adcolony.cpp \
		src/android/AndroidAdcolony.cpp




LOCAL_EXPORT_C_INCLUDES += \
					$(LOCAL_PATH)/src \
					$(LOCAL_PATH)/src/android \
					
					
include $(BUILD_STATIC_LIBRARY)
