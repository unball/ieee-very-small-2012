/**
 * @file      Camera.cpp
 * @author    George Andrew Brindeiro
 * @date      12/09/2012
 *
 * @attention Copyright (C) 2012
 * @attention UnBall Robot Soccer Team
 */

#include <camera.h>

Camera::Camera()
{
    Init();

    grab_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&Camera::grab_thread_function, this)));
}

Camera::~Camera()
{
    // Boost Thread
    grab_thread->join();

	// VideoCapture Interface
    cvReleaseImage(&cv_image_);
	
    // Stop transmission
    err = dc1394_video_set_transmission(camera, DC1394_OFF);

    // Stop capture
    err = dc1394_capture_stop(camera);

    // Power OFF
    dc1394_camera_set_power(camera, DC1394_OFF);

    // Cleanup camera
    dc1394_camera_free(camera);

    // Close dc1394
    dc1394_free(d);
}

bool Camera::Init()
{
	// VideoCapture Interface
	cv_image_ = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
	
    // Initialize libdc1394
    if ((d = dc1394_new ()) == NULL)
        return false;

    // Find cameras
    err = dc1394_camera_enumerate(d, &list);
    DC1394_ERR_RTN(err, "Failed to enumerate cameras");

    // Verify that we have at least one cameraDC1394_BYTE_ORDER_YUYV
    if(list->num == 0)
    {
        dc1394_log_error("No cameras found");
        return false;
    }

    // Work with first camera found
    if ((camera = dc1394_camera_new (d, list->ids[0].guid)) == NULL)
    {
        dc1394_log_error("Failed to initialize camera with guid %llx", list->ids[0].guid);
        return false;
    }

    // Not using the list anymore, clean it up
    dc1394_camera_free_list(list);

    // Power ON
    dc1394_camera_set_power(camera, DC1394_ON);

    // Print camera info 
    dc1394_camera_print_info(camera, stdout);

    // Setup capture
    err = dc1394_capture_setup(camera, 4, DC1394_CAPTURE_FLAGS_DEFAULT);
    
    // Set video mode
    dc1394_video_set_mode(camera, DC1394_VIDEO_MODE_640x480_YUV422);

    // Start transmission
    err = dc1394_video_set_transmission(camera, DC1394_ON);

	// VideoCapture Interface
	init_ = true;

    return true;
}

bool Camera::GrabFrame(IplImage* cv_image)
{
    boost::mutex::scoped_lock l(grab_mutex);

    // Capture dc1394 frame
    err = dc1394_capture_dequeue(camera, DC1394_CAPTURE_POLICY_WAIT, &frame);
    //DC1394_ERR_RTN(err,"Problem getting an image");

    // Release the buffer?
    err = dc1394_capture_enqueue(camera, frame);

    // Convert from YUV422 to RGB8
    dc1394_YUV422_to_RGB8(frame->image, dc1394_image, 640, 480, DC1394_BYTE_ORDER_UYVY);

    // Copy converted buffer to IplImage
    for (unsigned int i = 0; i < (640*480*3); i++)       
    {
        cv_image->imageData[i] = dc1394_image[i];
    }
    
    return true;
}

dc1394error_t Camera::dc1394_YUV422_to_RGB8(uint8_t *restrict src, uint8_t *restrict dest, uint32_t width, uint32_t height, uint32_t byte_order)
{
	register int i = ((width*height) << 1)-1;
	register int j = (width*height) + ( (width*height) << 1 ) -1;
	register int y0, y1, u, v;
	register int r, g, b;


	switch (byte_order)
	{
		case DC1394_BYTE_ORDER_YUYV:
			while (i >= 0)
			{
				v = (uint8_t) src[i--] -128;
				y1 = (uint8_t) src[i--];
				u = (uint8_t) src[i--] -128;
				y0 = (uint8_t) src[i--];
				YUV2BGR (y1, u, v, r, g, b);
				dest[j--] = b;
				dest[j--] = g;
				dest[j--] = r;
				YUV2BGR (y0, u, v, r, g, b);
				dest[j--] = b;
				dest[j--] = g;
				dest[j--] = r;
			}
			return DC1394_SUCCESS;
	
		case DC1394_BYTE_ORDER_UYVY:
			while (i >= 0)
			{
				y1 = (uint8_t) src[i--];
				v = (uint8_t) src[i--] - 128;
				y0 = (uint8_t) src[i--];
				u = (uint8_t) src[i--] - 128;
				YUV2BGR (y1, u, v, r, g, b);
				dest[j--] = b;
				dest[j--] = g;
				dest[j--] = r;
				YUV2BGR (y0, u, v, r, g, b);
				dest[j--] = b;
				dest[j--] = g;
				dest[j--] = r;
			}
			return DC1394_SUCCESS;
		default:
			return DC1394_INVALID_BYTE_ORDER;
	}

}
