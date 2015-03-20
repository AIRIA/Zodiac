LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/BaseLayer.cpp \
                   ../../Classes/BaseScene.cpp \
                   ../../Classes/HomeScene.cpp \
                   ../../Classes/VisibleRect.cpp \
                   ../../Classes/BaseSprite.cpp \
                   ../../Classes/ElasticButton.cpp \
                   ../../Classes/MainScene.cpp \
                   ../../Classes/LevelMap.cpp  \
                   ../../Classes/YZTableView.cpp \
                   ../../Classes/GameScene.cpp \
                   ../../Classes/TileMap.cpp \
                   ../../Classes/YZTile.cpp \
                   ../../Classes/GameMap.cpp 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
