//
// Created by Peter Hajtol on 30.4.17.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
#include "CCLI.h"
#include "constants.h"
#include "CException.h"


CCLI::CCLI() : CUI()
{
}



CCLI::~CCLI()
{
}



void CCLI::processInput(const std::string& in, CDatabase& db) const
{
    std::istringstream input(in);
    std::string command,parameter;

    if(!(input >> command)){
        std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_COMMAND_NONE << std::endl;
        return;
    }

    std::getline(input,parameter);
    parameter.erase(0,1);

    if (command == METASEARCH_COMMAND_HELP) {
        this->help();
    }

    else if(command == METASEARCH_COMMAND_SEARCH){
        std::istringstream params(parameter);
        std::string fileTypeStr, attributeStr, value;
        file_types fileType;
        file_attributes attribute;
        bool search = false, atr = false;

        if(attributeStr != "" && value == "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_INVALID << std::endl;

        params >> fileTypeStr;
        params >> attributeStr;
        std::getline(params,value);
        value.erase(0,1);

        if(fileTypeStr == "all") {
            fileType = ALL;
            search = true;
        } else if(fileTypeStr == "jpg") {
            fileType = IMAGE_JPEG;
            search = true;
        } else if(fileTypeStr == "png") {
            fileType = IMAGE_PNG;
            search = true;
        } else if(fileTypeStr == "image") {
            fileType = IMAGE;
            search = true;
        } else if(fileTypeStr == "txt") {
            fileType = TEXT_TXT;
            search = true;
        } else if(fileTypeStr == "video") {
            fileType = VIDEO;
            search = true;
        } else if(fileTypeStr == "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_NONE << std::endl;
        else
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_INVALID << std::endl;

        if(attributeStr == METASEARCH_FILE_ATTRIBUTE_NAME){
            attribute = FILE_FILENAME;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_PATH){
            attribute = FILE_PATH;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_SIZE){
            attribute = FILE_SIZE;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_WIDTH){
            attribute = IMG_VIDEO_WIDTH;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_HEIGHT){
            attribute = IMG_VIDEO_HEIGHT;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_MAKE){
            attribute = IMAGE_JPEG_MAKE;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_MODEL){
            attribute = IMAGE_JPEG_MODEL;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_LAT){
            attribute = IMAGE_JPEG_GPS_LATITUDE;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_LONG){
            attribute = IMAGE_JPEG_GPS_LONGITUDE;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_LENGTH){
            attribute = VIDEO_LENGTH;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_FRAMES){
            attribute = VIDEO_FRAMERATE;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_FORMAT){
            attribute = VIDEO_FORMAT;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_LINES){
            attribute = TEXT_LINES;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_WORDS){
            attribute = TEXT_WORDS;
            atr = true;
        } else if(attributeStr == METASEARCH_FILE_ATTRIBUTE_CHARS){
            attribute = TEXT_CHARS;
            atr = true;
        } else if(attributeStr != "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_NONE << std::endl;

        if(search) {
            std::vector< std::shared_ptr<CDatabaseEntry> > res;

            if(atr)
                res = db.search(fileType,attribute,value);
            else
                res = db.search(fileType);

            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << res.size() << " ";
            if(res.size() == 1)
                std::cout << METASEARCH_SEARCH_RESULTS_COUNT_SG << std::endl;
            else
                std::cout << METASEARCH_SEARCH_RESULTS_COUNT_PL << std::endl;

            for(unsigned int i = 0; i < res.size(); ++i) {
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
                std::cout << *res[i];
            }
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
        }
    }

    else if(command == METASEARCH_COMMAND_EXPORT){
        if(parameter == "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_NONE << std::endl;
        else
            try {
                db.exportDB(parameter);
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_SUCCESS_EXPORT << std::endl;
            }
            catch (const CException& exception){
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << exception.getError() << std::endl;
            }
    }

    else if(command == METASEARCH_COMMAND_IMPORT){
        if(parameter == "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_NONE << std::endl;
        else
            try {
                db.import(parameter);
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_SUCCESS_IMPORT << std::endl;
            }
            catch (const CException& exception) {
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << exception.getError() << std::endl;
            }

    }

    else if(command == METASEARCH_COMMAND_ADD){
        if(parameter == "")
            std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_PARAMETER_NONE << std::endl;
        else
            try {
                db.add(parameter);
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_SUCCESS_ADD << std::endl;
            }
            catch (const CException& exception){
                std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << exception.getError() << std::endl;
            }

    }

    else {
        std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " " << METASEARCH_ERROR_COMMAND_INVALID << std::endl;
    }
}



void CCLI::welcome() const
{
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " Welcome to Metasearch made by Peter Hajtol (hajtopet)" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " Start by typing command or show list of all commands with command \"" << METASEARCH_COMMAND_HELP << "\"" << std::endl;
}



void CCLI::help() const
{
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " This is a list of commands you can use:" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_ADD << " path-to-file\" - adds file to the database, path can be either relative or absolute" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \tsupported file extensions are: .jpg, .png, .txt, .mp4, .mov, .avi and .mkv" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_IMPORT << " path-to-file\" - imports database from file, path can be either relative or absolute" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_EXPORT << " path-to-file\" - exports database to the file, path can be either relative or absolute" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_SEARCH << " type attribute value\" - searches database for files of \"type\", which have \"attribute\" equal to \"value\" " << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\"attribute\" and \"value\" are optional, if not provided, Metasearch searches for all files of \"type\"" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\trecognised types are: \"all\", \"video\", \"image\", \"jpg\", \"png\", \"txt\"" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\trecognised attributes are:" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"name\", \"path\", \"size\" for all types" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"width\", \"height\" for types: video, image, jpg, png" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"make\", \"model\", \"latitude\", \"longitude\" for type jpg" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"length\", \"framerate\", \"format\" for type video" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"lines\", \"words\", \"chars\" for type txt" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\texamples:" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"search image width 1920\" - searches for all images, that have width equal to 1920" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"search jpg\" - searches for all jpg images" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << "\t\t\"search all\" - shows all files in database" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_HELP << "\" - shows this help" << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << std::endl;
    std::cout << METASEARCH_OUTPUT_LEADING_CHAR << " \"" << METASEARCH_COMMAND_EXIT << "\" - exits the Metasearch and discards any unexported changes in database" << std::endl;
}
