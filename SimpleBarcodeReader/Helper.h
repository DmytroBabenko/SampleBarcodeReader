//
//  Helper.hpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#ifndef Helper_h
#define Helper_h


#include <zbar.h>

namespace cv {
    class Mat;
}

zbar::Image ConvertOpenCVImageToZbarImage(const cv::Mat& iCVImage);

#endif /* Helper_h*/
