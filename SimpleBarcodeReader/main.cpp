//
//  main.cpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#include "BarcodeReader.h"
#include "Helper.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <iostream>


int main(int argc, const char * argv[])
{
    cv::VideoCapture cap(1); // open the video camera no. 0
    
    //cap.open(url);
    
    if (!cap.isOpened())  // if not success, exit program
    {
        std::cout << "Cannot open the video cam" << std::endl;
        return -1;
    }
    

    cv::namedWindow("Video",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

    
    while(true)
    {
        cv::Mat frame; // = cv::imread("/Users/dmytro.babenko/Desktop/Screen Shot 2017-09-21 at 10.46.07.png");
        
        bool bSuccess = cap.read(frame); // read a new frame from video
        
        cv::flip(frame, frame, 1);
        
        if (!bSuccess) //if not success, break loop
        {
            std::cout << "Cannot read a frame from video stream" << std::endl;
            break;
        }
        
        cv::Mat grey;
        cv::cvtColor(frame,grey, CV_BGR2GRAY);
    
        zbar::Image image = ConvertOpenCVImageToZbarImage(grey);
        
        std::list<BarcodeData> barcodeDatas =  BarcodeReader::ReadBarcodeFromImage(image, [&](const std::vector<cv::Point>& vp)
                                            {
                                                cv::RotatedRect r = minAreaRect(vp);
                                                cv::Point2f pts[4];
                                                r.points(pts);
                                                for(int i=0;i<4;i++)
                                                {
                                                    line(frame,pts[i],
                                                         pts[(i+1)%4],
                                                         cv::Scalar(255,0,0),
                                                         3);
                                                }

                                            });
        cv::imshow("Video", frame);
        
        for (const auto& barcodeData : barcodeDatas)
        {
            std::cout<<"Barcode type: "<<barcodeData.mType<<" , data: "<<barcodeData.mData<<std::endl;
        }
        
        
        if (cv::waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
        {
            std::cout << "esc key is pressed by user" << std::endl;
            break;
        }


    }
    
    
    return 0;
}
