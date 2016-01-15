/**
 * @file      Camera.h
 * @author    George Andrew Brindeiro
 * @date      12/09/2012
 *
 * @attention Copyright (C) 2012
 * @attention UnBall Robot Soccer Team
 */

#ifndef CAMERA_H
#define CAMERA_H

#define YUV2BGR(y, u, v, r, g, b)\
b = y + ((v*1436) >> 10);\
g = y - ((u*352 + v*731) >> 10);\
r = y + ((u*1814) >> 10);\
r = r < 0 ? 0 : r;\
g = g < 0 ? 0 : g;\
b = b < 0 ? 0 : b;\
r = r > 255 ? 255 : r;\
g = g > 255 ? 255 : g;\
b = b > 255 ? 255 : b

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>

#include <inttypes.h>

#include <dc1394/dc1394.h>

#include <cv.h>
#include <highgui.h>

#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>

class Camera
{
    public:
        Camera();
        ~Camera();

        bool GrabFrame(IplImage* cv_image);
        
        // VideoCapture Interface
        inline void open(const char path[])		{ /* Do nothing, opened in constructor*/ }
        inline bool isOpened()	{ return init_;}
        inline void release()	{ /* Do nothing, released in destructor */ }
        
        inline bool grab()		{ return GrabFrame(cv_image_); }
        inline void retrieve(cv::Mat& frame, int channel) { frame = cv_image_; }

        inline void grab_thread_function() { while(true){ grab(); usleep(10000);} }

    private:
		bool init_;
    
        bool Init();
        dc1394error_t dc1394_YUV422_to_RGB8(uint8_t *restrict src, uint8_t *restrict dest, uint32_t width, uint32_t height, uint32_t byte_order);

        dc1394camera_t* camera;
        dc1394video_frame_t* frame;

        dc1394_t* d;
        dc1394camera_list_t* list;
        dc1394error_t err;

        uint8_t dc1394_image[640*480*3];
        
        // VideoCapture Interface
        IplImage* cv_image_;

        // Boost Threads
        boost::shared_ptr<boost::thread> grab_thread;
        boost::mutex grab_mutex;
};

#endif // CAMERA_H

