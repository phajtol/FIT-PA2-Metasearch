//
// Created by Peter Hajtol on 7.5.17.
//

#include <iostream>
#include <fstream>
#include <netinet/in.h>
#include "CPNGImage.h"
#include "constants.h"


CPNGImage::CPNGImage(const std::string &file) : CImage(file)
{
    std::ifstream in(file);

    //in PNG image, width is a 4-byte int at offset 16 and height is also 4-byte int at offset 20
    in.seekg(16);
    in.read((char*) &width, 4);
    in.read((char*) &height, 4);

    //in case image uses other endian-ness
    width = ntohl(width);
    height = ntohl(height);
}



CPNGImage::CPNGImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height)
        :
        CImage(path,filename,size,width,height)
{
}



CPNGImage::~CPNGImage()
{
}



std::ostream& CPNGImage::print(std::ostream& os) const
{
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_NAME << ": " << fileName << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_PATH << ": " << path << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_SIZE << ": " << size << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_WIDTH << ": " << width << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_HEIGHT << ": " << height << std::endl;
    return os;
}



std::ofstream& CPNGImage::serialize(std::ofstream& os) const
{
    os << METASEARCH_EXPORT_TAG_PNG
       << METASEARCH_EXPORT_DELIMETER << path
       << METASEARCH_EXPORT_DELIMETER << fileName
       << METASEARCH_EXPORT_DELIMETER << size
       << METASEARCH_EXPORT_DELIMETER << width
       << METASEARCH_EXPORT_DELIMETER << height;
    return os;
}
