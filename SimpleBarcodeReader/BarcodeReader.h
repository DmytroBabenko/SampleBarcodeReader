//
//  BarcodeReader.hpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#ifndef BarcodeReader_h
#define BarcodeReader_h


#include "BarcodeData.h"

#include <list>
#include <functional>
#include <array>

#include <opencv2/core/core.hpp>


namespace zbar {
    class Image;
}



class BarcodeReader
{
public:
    
    static std::list<BarcodeData> ReadBarcodeFromImage(zbar::Image& image, std::function<void(const std::vector<cv::Point>& vp)> iBarcodeBoxProcessor = nullptr);
    
};

#endif /* BarcodeReader_h */
