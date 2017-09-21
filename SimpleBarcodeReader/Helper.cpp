//
//  Helper.cpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#include "Helper.h"

#include <opencv2/core/core.hpp>

zbar::Image ConvertOpenCVImageToZbarImage(const cv::Mat& iCVImage)
{
    int width = iCVImage.cols;
    int height = iCVImage.rows;
    unsigned char *raw = (unsigned char *)iCVImage.data;
    // wrap image data
    zbar::Image image(width, height, "Y800", raw, width * height);
    
    return image;

}
