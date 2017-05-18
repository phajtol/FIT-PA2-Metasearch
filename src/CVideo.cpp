//
// Created by Peter Hajtol on 16.5.17.
//

#include <iostream>
#include <fstream>
#include "CVideo.h"
#include "constants.h"

//in case ProgTest doesn't support MediaInfo library
#ifndef __PROGTEST__
#include <MediaInfo/MediaInfo.h>
#endif /* __PROGTEST_ */

CVideo::CVideo(const std::string &file)
        :
        CMedia(file)
{
    #ifndef __PROGTEST__
    std::wstring wbuffer;
    std::string buffer;
    MediaInfoLib::String mediainfofile (file.begin(),file.end());
    MediaInfoLib::MediaInfo video;
    video.Option(L"Internet", L"No");
    video.Open(mediainfofile);

    //load video width from video file and then convert it to unsigned int
    wbuffer = video.Get(MediaInfoLib::Stream_Video, 0, MediaInfoLib::String(L"Width"));
    buffer.assign(wbuffer.begin(),wbuffer.end());
    width = (unsigned int) stoul(buffer);

    //load video height from video file and then convert it to unsigned int
    wbuffer = video.Get(MediaInfoLib::Stream_Video, 0, MediaInfoLib::String(L"Height"));
    buffer.assign(wbuffer.begin(),wbuffer.end());
    height = (unsigned int) stoul(buffer);

    //load video duration from video file and then convert it to unsigned int
    wbuffer = video.Get(MediaInfoLib::Stream_Video, 0, MediaInfoLib::String(L"Duration"));
    buffer.assign(wbuffer.begin(),wbuffer.end());
    length = (unsigned int) (stoul(buffer) / 1000) + 1; //+1 because conversion to unsigned int rounds down and length is always rounded up

    //load video framerate from video file and then convert it to double
    wbuffer = video.Get(MediaInfoLib::Stream_Video, 0, MediaInfoLib::String(L"FrameRate"));
    buffer.assign(wbuffer.begin(),wbuffer.end());
    framerate = stod(buffer);

    //load format from video file and then convert it to std::string
    wbuffer = video.Get(MediaInfoLib::Stream_General, 0, MediaInfoLib::String(L"Format"));
    format.assign(wbuffer.begin(),wbuffer.end());

    video.Close();

    #else
    width = 0;
    height= 0;
    length = 0;
    framerate = 0.0;
    format = "Unknown";
    #endif /* __PROGTEST_ */
}



CVideo::CVideo(const std::string &path, const std::string &filename, unsigned int size, unsigned int width,
               unsigned int height, unsigned int length, double framerate, const std::string& format)
        :
        CMedia(path,filename,size,width,height),
        length(length),
        framerate(framerate),
        format(format)
{
}



CVideo::~CVideo()
{
}


unsigned int CVideo::getLength() const
{
    return length;
}



double CVideo::getFramerate() const
{
    return framerate;
}



std::string CVideo::getFormat() const
{
    return format;
}



std::ostream& CVideo::print(std::ostream &os) const
{
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_NAME << ": " << fileName << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_PATH << ": " << path << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_SIZE << ": " << size << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_WIDTH << ": " << width << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_HEIGHT << ": " << height << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_LENGTH << ": " << length << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_FRAMES << ": " << framerate << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_FORMAT << ": " << format << std::endl;
    return os;
}



std::ofstream& CVideo::serialize(std::ofstream &os) const
{
    os << METASEARCH_EXPORT_TAG_VIDEO
       << METASEARCH_EXPORT_DELIMETER << path
       << METASEARCH_EXPORT_DELIMETER << fileName
       << METASEARCH_EXPORT_DELIMETER << size
       << METASEARCH_EXPORT_DELIMETER << width
       << METASEARCH_EXPORT_DELIMETER << height
       << METASEARCH_EXPORT_DELIMETER << length
       << METASEARCH_EXPORT_DELIMETER << framerate
       << METASEARCH_EXPORT_DELIMETER << format;
    return os;
}
