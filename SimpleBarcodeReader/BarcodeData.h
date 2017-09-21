//
//  BarcodeData.hpp
//  SimpleBarcodeReader
//
//  Created by Dmytro Babenko on 9/20/17.
//  Copyright © 2017 Dmytro Babenko. All rights reserved.
//
#include <string>

#ifndef BarcodeData_h
#define BarcodeData_h

struct BarcodeData
{
    BarcodeData(const std::string& iType, const std::string& iData);
    
    std::string mType;
    std::string mData;
};


#endif /* BarcodeData_h */
