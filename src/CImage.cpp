//
// Created by Peter Hajtol on 11.5.17.
//

#include "CImage.h"


CImage::CImage(const std::string &file)
        :
        CMedia(file)
{
}



CImage::CImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height)
        :
        CMedia(path,filename,size,width,height)
{
}



CImage::~CImage()
{
}
