//
//  main.cpp
//  test1
//
//  Created by Dmytro Babenko on 9/13/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#include <iostream>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

#include <zbar.h>


//#include <zxing/qrcode/QRCodeReader.h>
//#include <zxing/common/GlobalHistogramBinarizer.h>
//#include <zxing/common/LocalBlockBinarizer.h>
//#include <zxing/Exception.h>

using namespace cv;
using namespace zbar;


int main()
{
    cv::Mat image =  cv::imread("/Users/dmytro.babenko/Desktop/Screen Shot 2017-09-21 at 11.52.15.png", 0);
    
    cv::Mat dst;
    cv::threshold(image, dst, 127, 255, 0);
    
    
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    
    cv::findContours(dst, contours, hierarchy, 1, 2);
    
    std::vector<cv::Point> cnt = contours[0];
    
    cv::Moments m =  cv::moments(cnt);
    
    
    RotatedRect rect = cv::minAreaRect(cnt);
    
    std::vector<cv::Point> box;
    cv::boxPoints(rect, box);
    
    
    
    cv::drawContours(image, std::vector<std::vector<cv::Point>>(1, box), 0, cv::Scalar(0, 255, 0), 2);
    
    cv::imwrite("/Volumes/data/2.png", image);
    
}



//int main(int argc, char* argv[])
//{
//
//    VideoCapture cap(1); // open the video camera no. 0
//    
//    
//    if (!cap.isOpened())  // if not success, exit program
//    {
//        std::cout << "Cannot open the video cam" << std::endl;
//        return -1;
//    }
//    
//    
////    ImageScanner scanner;
////    scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
////    
////    double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
////    double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video
//    
////    std::cout << "Frame size : " << dWidth << " x " << dHeight << std::endl;
//    
//    //namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"
//    
//    while (1)
//    {
//        Mat frame; // = cv::imread("/Users/dmytro.babenko/Desktop/Screen Shot 2017-09-20 at 16.35.07.png");
//        
//        bool bSuccess = cap.read(frame); // read a new frame from video
//        
//        if (!bSuccess) //if not success, break loop
//        {
//            std::cout << "Cannot read a frame from video stream" << std::endl;
//            break;
//        }
//        
//        /*
//        Mat grey;
//        cvtColor(frame,grey,CV_BGR2GRAY);
//        
//        cv::imwrite("/Volumes/data/1.png", grey);
//        
//        int width = grey.cols;
//        int height = grey.rows;
//        uchar *raw = (uchar *)grey.data;
//        // wrap image data
//        Image image(width, height, "Y800", raw, width * height);
//        // scan the image for barcodes
//        int n = scanner.scan(image);
//        // extract results
//        /*for(Image::SymbolIterator symbol = image.symbol_begin();
//            symbol != image.symbol_end();
//            ++symbol) {
//            std::vector<Point> vp;
//            // do something useful with results
//            std::cout << "decoded " << symbol->get_type_name()  << " symbol \"" << symbol->get_data() << '"' <<" "<< std::endl;
//            int n = symbol->get_location_size();
//            for(int i=0;i<n;i++){
//                vp.push_back(Point(symbol->get_location_x(i),symbol->get_location_y(i)));
//            }
//            RotatedRect r = minAreaRect(vp);
//            Point2f pts[4];
//            r.points(pts);
//            for(int i=0;i<4;i++){
//                line(frame,pts[i],pts[(i+1)%4],Scalar(255,0,0),3);
//            }
//            //cout<<"Angle: "<<r.angle<<endl;
//        }*/
//        
//        imshow("MyVideo", frame); //show the frame in "MyVideo" window
//        
//        if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
//        {
//            std::cout << "esc key is pressed by user" << std::endl;
//            break; 
//        }
//    }
//    
//    return 0;
//    
//}


/*
int main(int argc, const char * argv[])
{
    
    cv::VideoCapture capture(0);
    
    while (true)
    {
        cv::Mat webcam;
        capture.read(webcam);
        cv::imshow("Webcam", webcam);
        
        //cv::imwrite("/Volumes/data/1.png", webcam);
        
    
    
    
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    // obtain image data
    const char* file = "/Users/dmytro.babenko/Desktop/Screen Shot 2017-09-19 at 13.36.23.png";
    cv::Mat img = webcam;
    cv::Mat imgout;
    cvtColor(img,imgout,CV_GRAY2RGB);
    int width = img.cols;
    int height = img.rows;
    uchar *raw = (uchar *)img.data;
    // wrap image data
    zbar::Image image(width, height, "Y800", raw, width * height);

    // scan the image for barcodes
    int n = scanner.scan(image);
    // extract results
        
        
        bool found = false;
    for(zbar::Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol) {
        std::vector<cv::Point> vp;
        // do something useful with results
        std::cout << "decoded " << symbol->get_type_name()
        << " symbol \"" << symbol->get_data() << '"' <<" "<< std::endl;
        int n = symbol->get_location_size();
        for(int i=0;i<n;i++){
            vp.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }
        cv::RotatedRect r = minAreaRect(vp);
        cv::Point2f pts[4];
        r.points(pts);
        for(int i=0;i<4;i++){
            line(imgout,pts[i],pts[(i+1)%4],cv::Scalar(255,0,0),3);
        }
        std::cout<<"Angle: "<<r.angle<<std::endl;
        found = true;
    }
        
        if (found)
        {
            break;
        }
    
        cv::imshow("imgout.jpg",imgout);
    // clean up
        image.set_data(NULL, 0);
    }
    cv::waitKey();
    
    return 0;
}

*/



//https://github.com/bharathp666/opencv_qr/blob/master/image.cpp

