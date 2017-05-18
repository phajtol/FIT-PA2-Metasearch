//
// Created by Peter Hajtol on 16.5.17.
//

#include "CMedia.h"



CMedia::CMedia(const std::string& file)
        :
        CDatabaseEntry(file)
{
}



CMedia::CMedia(const std::string& path, const std::string& filename, unsigned int size, unsigned int width,
               unsigned int height)
        :
        CDatabaseEntry(path,filename,size),
        width(width),
        height(height)
{
}



CMedia::~CMedia()
{

}



unsigned int CMedia::getWidth() const
{
    return width;
}



unsigned int CMedia::getHeight() const
{
    return height;
}
