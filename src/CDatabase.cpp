//
// Created by Peter Hajtol on 30.4.17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include "CDatabase.h"
#include "CJPEGImage.h"
#include "CPNGImage.h"
#include "CTextFile.h"
#include "constants.h"
#include "CException.h"
#include "CVideo.h"


CDatabase::CDatabase()
{
}



CDatabase::~CDatabase()
{
}



void CDatabase::add(const std::string& file)
{
    std::ifstream infile(file);

    if(!infile.good())
        throw CException(METASEARCH_ERROR_FILE_READING + file);

    std::string extension = file.substr(file.size() - 3);

    if(!strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_JPEG.c_str()))
        data.push_back(std::make_shared<CJPEGImage>(CJPEGImage(file)));

    else if (!strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_PNG.c_str()))
        data.push_back(std::make_shared<CPNGImage>(CPNGImage(file)));

    else if(!strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_TXT.c_str()))
        data.push_back(std::make_shared<CTextFile>(CTextFile(file)));

    else if(!strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_VIDEO_1.c_str()) ||
            !strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_VIDEO_2.c_str()) ||
            !strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_VIDEO_3.c_str()) ||
            !strcasecmp(extension.c_str(),METASEARCH_FILE_EXTENSION_VIDEO_4.c_str()))
        data.push_back(std::make_shared<CVideo>(CVideo(file)));

    else
        throw CException(METASEARCH_ERROR_UNSUPPORTED_EXTENSION);

    infile.close();
}



void CDatabase::exportDB(const std::string& file) const
{
    std::ofstream outfile(file);

    if(outfile.fail())
        throw CException(METASEARCH_ERROR_EXPORT_FILE_FAIL);

    for(unsigned int i = 0; i < data.size(); ++i)
        outfile << *data[i] << std::endl;

    outfile.close();
}



void CDatabase::import(const std::string& file)
{
    std::ifstream infile(file);

    if(!infile.good())
        throw CException(METASEARCH_ERROR_IMPORT_FILE_FAIL);

    std::string line,filename,path;
    unsigned int size;
    char delimeter;

    while(std::getline(infile,line)){
        std::istringstream lineStream;
        std::string fileType;

        lineStream.str(line);
        std::getline(lineStream,fileType,METASEARCH_EXPORT_DELIMETER);

        std::getline(lineStream,path,METASEARCH_EXPORT_DELIMETER);
        std::getline(lineStream,filename,METASEARCH_EXPORT_DELIMETER);
        lineStream >> size;
        lineStream >> delimeter;

        if(fileType == METASEARCH_EXPORT_TAG_JPG){
            std::string make,model;
            unsigned int width,height;
            double latitude,longitude;

            lineStream >> width;
            lineStream >> delimeter;
            lineStream >> height;
            lineStream >> delimeter;
            std::getline(lineStream,make,METASEARCH_EXPORT_DELIMETER);
            std::getline(lineStream,model,METASEARCH_EXPORT_DELIMETER);
            lineStream >> latitude;
            lineStream >> delimeter;
            lineStream >> longitude;

            data.push_back(std::make_shared<CJPEGImage>(CJPEGImage(path,filename,size,width,height,make,model,latitude,longitude)));
        }
        else if (fileType == METASEARCH_EXPORT_TAG_PNG){
            unsigned int width,height;

            lineStream >> width;
            lineStream >> delimeter;
            lineStream >> height;

            data.push_back(std::make_shared<CPNGImage>(CPNGImage(path,filename,size,width,height)));
        }
        else if (fileType == METASEARCH_EXPORT_TAG_TXT){
            unsigned int lines,words,chars;

            lineStream >> lines;
            lineStream >> delimeter;
            lineStream >> words;
            lineStream >> delimeter;
            lineStream >> chars;

            data.push_back(std::make_shared<CTextFile>(CTextFile(path,filename,size,lines,words,chars)));
        }
        else if (fileType == METASEARCH_EXPORT_TAG_VIDEO){
            unsigned int width,height,length;
            double framerate;
            std::string format;

            lineStream >> width;
            lineStream >> delimeter;
            lineStream >> height;
            lineStream >> delimeter;
            lineStream >> length;
            lineStream >> delimeter;
            lineStream >> framerate;
            lineStream >> delimeter;
            lineStream >> format;

            data.push_back(std::make_shared<CVideo>(CVideo(path,filename,size,width,height,length,framerate,format)));
        }
    }

    infile.close();
}



std::vector<std::shared_ptr<CDatabaseEntry> > CDatabase::search(file_types fileType, file_attributes fileAttribute,
                                                                const std::string& needle) const
{
    std::vector<std::shared_ptr<CDatabaseEntry> > results;

    for(unsigned int i = 0; i < data.size(); ++i){
        if(isFileType(fileType,data[i])) {
            switch(fileAttribute){
                case FILE_FILENAME:
                    if(data[i]->getFileName() == needle)
                        results.push_back(data[i]);
                    break;

                case FILE_PATH:
                    if(data[i]->getPath() == needle)
                        results.push_back(data[i]);
                    break;

                case FILE_SIZE:
                    if(data[i]->getSize() == stoul(needle))
                        results.push_back(data[i]);
                    break;

                case IMG_VIDEO_WIDTH: {
                    if(std::shared_ptr<CMedia> pointer = std::dynamic_pointer_cast<CMedia>(data[i]))
                        if(pointer->getWidth() == stoul(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case IMG_VIDEO_HEIGHT:{
                    if(std::shared_ptr<CMedia> pointer = std::dynamic_pointer_cast<CMedia>(data[i]))
                        if(pointer->getHeight() == stoul(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case IMAGE_JPEG_MAKE:{
                    if(std::shared_ptr<CJPEGImage> pointer = std::dynamic_pointer_cast<CJPEGImage>(data[i]))
                        if(pointer->getMake() == needle)
                            results.push_back(data[i]);
                        }
                    break;

                case IMAGE_JPEG_MODEL:{
                    if(std::shared_ptr<CJPEGImage> pointer = std::dynamic_pointer_cast<CJPEGImage>(data[i]))
                        if(pointer->getModel() == needle)
                            results.push_back(data[i]);
                        }
                    break;

                case IMAGE_JPEG_GPS_LATITUDE:{
                    if(std::shared_ptr<CJPEGImage> pointer = std::dynamic_pointer_cast<CJPEGImage>(data[i]))
                        if(pointer->getLatitude() == stod(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case IMAGE_JPEG_GPS_LONGITUDE:{
                    if(std::shared_ptr<CJPEGImage> pointer = std::dynamic_pointer_cast<CJPEGImage>(data[i]))
                        if(pointer->getLongitude() == stod(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case VIDEO_LENGTH:{
                    if(std::shared_ptr<CVideo> pointer = std::dynamic_pointer_cast<CVideo>(data[i]))
                        if(pointer->getLength() == stoul(needle))
                            results.push_back(data[i]);
                    }
                    break;

                case VIDEO_FRAMERATE:{
                    if(std::shared_ptr<CVideo> pointer = std::dynamic_pointer_cast<CVideo>(data[i]))
                        if(pointer->getFramerate() == stod(needle))
                            results.push_back(data[i]);
                    }
                    break;

                case VIDEO_FORMAT:{
                    if(std::shared_ptr<CVideo> pointer = std::dynamic_pointer_cast<CVideo>(data[i]))
                        if(pointer->getFormat() == needle)
                            results.push_back(data[i]);
                    }
                    break;

                case TEXT_LINES:{
                    if(std::shared_ptr<CTextFile> pointer = std::dynamic_pointer_cast<CTextFile>(data[i]))
                        if(pointer->getLines() == stoul(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case TEXT_WORDS:{
                    if(std::shared_ptr<CTextFile> pointer = std::dynamic_pointer_cast<CTextFile>(data[i]))
                        if(pointer->getWords() == stoul(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case TEXT_CHARS:{
                    if(std::shared_ptr<CTextFile> pointer = std::dynamic_pointer_cast<CTextFile>(data[i]))
                        if(pointer->getChars() == stoul(needle))
                            results.push_back(data[i]);
                        }
                    break;

                case NONE:
                    results.push_back(data[i]);
                    break;
            }
        }
    }

    return results;
}



bool CDatabase::isFileType(file_types fileType, std::shared_ptr<CDatabaseEntry> entry) const
{
    switch(fileType){
        case VIDEO: {
            std::shared_ptr<CVideo> pointer = std::dynamic_pointer_cast<CVideo>(entry);
            return pointer != nullptr;
        }
        case IMAGE: {
            std::shared_ptr<CImage> pointer = std::dynamic_pointer_cast<CImage>(entry);
            return pointer != nullptr;
        }
        case IMAGE_JPEG: {
            std::shared_ptr<CJPEGImage> pointer = std::dynamic_pointer_cast<CJPEGImage>(entry);
            return pointer != nullptr;
        }
        case IMAGE_PNG:{
            std::shared_ptr<CPNGImage> pointer = std::dynamic_pointer_cast<CPNGImage>(entry);
            return pointer != nullptr;
        }
        case TEXT_TXT: {
            std::shared_ptr<CTextFile> pointer = std::dynamic_pointer_cast<CTextFile>(entry);
            return pointer != nullptr;
        }
        case ALL: return true;
        default: return false;
    }
}
