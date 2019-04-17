
-include .config

OPENCV_PATH=$(CONFIG_OPENCV_PATH)

#opencv includes
OPENCV_INC_host = -I $(OPENCV_PATH)/OpenCV3.0.0/linux-obj_rel/include
OPENCV_INC_host += -I $(OPENCV_PATH)/OpenCV3.0.0/linux-obj_rel/include/opencv2

OPENCV_INC_target = -I $(OPENCV_PATH)/OpenCV3.0.0/arm-obj_rel/include
OPENCV_INC_target += -I $(OPENCV_PATH)/OpenCV3.0.0/arm-obj_rel/include/opencv2


#opencv libs
LIBS+=-lopencv_shape
LIBS+=-lopencv_stitching
LIBS+=-lopencv_objdetect
LIBS+=-lopencv_superres
LIBS+=-lopencv_videostab
LIBS+=-lopencv_calib3d
LIBS+=-lopencv_features2d
LIBS+=-lopencv_highgui
LIBS+=-lopencv_videoio
LIBS+=-lopencv_imgcodecs
LIBS+=-lopencv_video
LIBS+=-lopencv_photo
LIBS+=-lopencv_ml
LIBS+=-lopencv_imgproc
LIBS+=-lopencv_flann
LIBS+=-lopencv_core
LIBS+=-lopencv_hal
LIBS+=-lopencv_ts


#opencv 3rd party libs
LIBS+=-llibjpeg
LIBS+=-llibwebp
LIBS+=-llibpng
LIBS+=-llibtiff
LIBS+=-llibjasper
LIBS+=-lIlmImf

LIBS+=-ldl
LIBS+=-lrt
LIBS+=-lm -lpthread
LIBS+=-lzlib

OPENCV_LIBS_host := -L$(OPENCV_PATH)/OpenCV3.0.0/linux-obj_rel/lib
OPENCV_LIBS_host += -L$(OPENCV_PATH)/OpenCV3.0.0/linux-obj_rel/share/OpenCV/3rdparty/lib/
OPENCV_LIBS_host += $(LIBS)

OPENCV_LIBS_target := -L$(OPENCV_PATH)/OpenCV3.0.0/arm-obj_rel/lib 
OPENCV_LIBS_target += -L$(OPENCV_PATH)/OpenCV3.0.0/arm-obj_rel/share/OpenCV/3rdparty/lib/
OPENCV_LIBS_target += $(LIBS)