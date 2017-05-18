//
// Created by Peter Hajtol on 6.5.17.
//

#include <iostream>
#include <fstream>
#include <libexif/exif-data.h>
#include <sstream>
#include <cstring>
#include "CJPEGImage.h"
#include "constants.h"


CJPEGImage::CJPEGImage(const std::string& file)
        :
        CImage(file)
{
    //libexif leaks memory, tested with calls to library functions in comment block

    char* buffer = new char [METASEARCH_EXIF_BUFFER_SIZE+1];
    char* GPSref = new char [3];
    ExifData *image = exif_data_new_from_file(file.c_str());

    //load image width from file, 0 if no width data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_EXIF],ExifTag(EXIF_TAG_PIXEL_X_DIMENSION)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(strcmp(buffer,"") == 0) width = 0;
    else width = (unsigned int) std::stoul(buffer);
    strncpy(buffer,"",METASEARCH_EXIF_BUFFER_SIZE);

    //load image height from file, 0 if no height data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_EXIF],ExifTag(EXIF_TAG_PIXEL_Y_DIMENSION)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(strcmp(buffer,"") == 0) height = 0;
    else height = (unsigned int) std::stoul(buffer);
    strncpy(buffer,"",METASEARCH_EXIF_BUFFER_SIZE);

    //load camera make from file, "Unknown" if no camera make data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[0],ExifTag(EXIF_TAG_MAKE)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(strcmp(buffer,"") == 0) make = "Unknown";
    else make = buffer;
    strncpy(buffer,"",METASEARCH_EXIF_BUFFER_SIZE);

    //load camera model from file, "Unknown" if no camera model data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[0],ExifTag(EXIF_TAG_MODEL)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(strcmp(buffer,"") == 0) model = "Unknown";
    else model = buffer;
    strncpy(buffer,"",METASEARCH_EXIF_BUFFER_SIZE);

    //load GPS latitude from file, 0 if no latitude data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_GPS],ExifTag(EXIF_TAG_GPS_LATITUDE_REF)),GPSref,2);
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_GPS],ExifTag(EXIF_TAG_GPS_LATITUDE)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(!parseGPS(buffer,GPSref,&latitude)) latitude = 0;
    strncpy(buffer,"",METASEARCH_EXIF_BUFFER_SIZE);
    strncpy(GPSref,"",3);

    //load GPS longitude from file, 0 if no longitude data found
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_GPS],ExifTag(EXIF_TAG_GPS_LONGITUDE_REF)),GPSref,2);
    exif_entry_get_value(exif_content_get_entry(image->ifd[EXIF_IFD_GPS],ExifTag(EXIF_TAG_GPS_LONGITUDE)),buffer,METASEARCH_EXIF_BUFFER_SIZE);
    if(!parseGPS(buffer,GPSref,&longitude)) longitude = 0;


    delete [] buffer;
}



CJPEGImage::CJPEGImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height,
                       const std::string& make, const std::string& model, double latitude, double longitude)
        :
        CImage(path,filename,size,width,height),
        make(make),
        model(model),
        latitude(latitude),
        longitude(longitude)
{
}



CJPEGImage::~CJPEGImage()
{
}



std::ostream& CJPEGImage::print(std::ostream& os) const
{
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_NAME << ": " << fileName << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_PATH << ": " << path << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_SIZE << ": " << size << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_WIDTH << ": " << width << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_HEIGHT << ": " << height << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_MAKE << ": " << make << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_MODEL << ": " << model<< std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_LAT << ": " << latitude << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_LONG << ": " << longitude << std::endl;
    return os;
}



std::ofstream& CJPEGImage::serialize(std::ofstream& os) const
{
    os << METASEARCH_EXPORT_TAG_JPG
       << METASEARCH_EXPORT_DELIMETER << path
       << METASEARCH_EXPORT_DELIMETER << fileName
       << METASEARCH_EXPORT_DELIMETER << size
       << METASEARCH_EXPORT_DELIMETER << width
       << METASEARCH_EXPORT_DELIMETER << height
       << METASEARCH_EXPORT_DELIMETER << make
       << METASEARCH_EXPORT_DELIMETER << model
       << METASEARCH_EXPORT_DELIMETER << latitude
       << METASEARCH_EXPORT_DELIMETER << longitude;
    return os;
}


std::string CJPEGImage::getMake() const
{
    return make;
}



std::string CJPEGImage::getModel() const
{
    return model;
}



double CJPEGImage::getLatitude() const
{
    return latitude;
}



double CJPEGImage::getLongitude() const
{
    return longitude;
}


bool CJPEGImage::parseGPS(const char* in, const char* ref, double* out) const
{
    //input will be from exif, input format: ex. "49, 10, 5"
    double temp;
    char comma;
    std::istringstream input;
    input.str((std::string) in);
    *out = 0;
    if(!(input >> temp)) return false;
    *out += temp;
    if(!(input >> comma)) return false;
    if(!(input >> temp)) return false;
    *out += temp/60;
    if(!(input >> comma)) return false;
    if(!(input >> temp)) return false;
    *out += temp/3600;
    //if the coordinates reference is north or west, coordinates will be negative
    if(!strcmp(ref,"S") || !strcmp(ref,"W"))
        *out *= -1;
    return true;
}