//
//  BarcodeReader.cpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//

#include "BarcodeReader.h"


#include <zbar.h>


std::list<BarcodeData> BarcodeReader::ReadBarcodeFromImage(zbar::Image& image,
                                            std::function<void(const std::vector<cv::Point>& vp)> iBarcodeBoxProcessor /*= nullptr*/)
{
    zbar::ImageScanner scanner;
    scanner.set_config(zbar::ZBAR_NONE, zbar::ZBAR_CFG_ENABLE, 1);
    
    scanner.scan(image);
    
    
    std::list<BarcodeData> barcodeDatas;
    
    for(zbar::Image::SymbolIterator symbol = image.symbol_begin();
        symbol != image.symbol_end();
        ++symbol)
    {
        barcodeDatas.push_back(BarcodeData(symbol->get_type_name(), symbol->get_data()));
        
        std::vector<cv::Point> vp;
        
        int n = symbol->get_location_size();
        for(int i=0;i<n;i++){
            vp.push_back(cv::Point(symbol->get_location_x(i),symbol->get_location_y(i)));
        }
        
        if (iBarcodeBoxProcessor)
        {
            iBarcodeBoxProcessor(vp);
        }
        
    }
    
    return barcodeDatas;
    

}
