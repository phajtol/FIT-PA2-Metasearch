//
// Created by Peter Hajtol on 30.4.17.
//

#include <zconf.h>
#include <iostream>
#include <fstream>
#include "CDatabaseEntry.h"



CDatabaseEntry::CDatabaseEntry(const std::string& file)
{
    //fileName takes the substring after last '/' from given path to file
    fileName = file.substr(file.find_last_of("/") + 1);

    if (file[0] == '/') {
        //if given path to file is absolute, path to file's directory is everything until last '/'
        path = file.substr(0,positionOfNthOccurrence('/',file,substringOccurrences("/",file)));
    } else {
        char buff[64];
        getcwd(buff,64);
        std::string currentDir(buff);

        if(file.find("../") == file.npos && file.find('/') == file.npos){
            // if we received path to file in program's current directory
            // (path doesn't contain neither "../" nor '/')
            // path is simply program's current directory
            path = currentDir + '/';
        } else if(file.find("../") == file.npos) {
            // if we received path to file that is deeper than program's current directory
            // path is program's current directory + path to file until last '/'
            path = currentDir + "/" + file.substr(0,file.find_last_of("/"));
        } else {
            // otherwise we received path to file that is in directory "higher" than our program's
            // so we have to remove X directories from our program's directory, where X is number of "../" in path to file
            path = currentDir.substr(0, positionOfNthOccurrence('/', currentDir, substringOccurrences("/", currentDir) -
                                                                                 substringOccurrences("../", file) +
                                                                                 1));

            // and if there are some directories between "../" and file name, we must add them to the path
            if(substringOccurrences("/",file.substr(file.rfind("../") + 3)) != 0)
                path += file.substr(file.rfind("../") + 3, file.length() - file.rfind("../") - 3 - fileName.length());

        }
    }

    std::ifstream in(file,std::ios::binary | std::ios::ate);
    size = (unsigned int) in.tellg();
    in.close();

}



CDatabaseEntry::CDatabaseEntry(const std::string& path, const std::string& filename, unsigned int size)
        :
        fileName(filename),
        path(path),
        size(size)
{
}



CDatabaseEntry::~CDatabaseEntry()
{
}



std::string CDatabaseEntry::getFileName() const
{
    return fileName;
}



std::string CDatabaseEntry::getPath() const
{
    return path;
}



unsigned int CDatabaseEntry::getSize() const
{
    return size;
}



unsigned int CDatabaseEntry::substringOccurrences(const std::string& needle, const std::string& haystack) const
{
    std::string::size_type pos = 0;
    unsigned int occurrences = 0;
    while ((pos = haystack.find(needle,pos)) != std::string::npos) {
        ++occurrences;
        pos += needle.length();
    }
    return occurrences;
}



std::string::size_type CDatabaseEntry::positionOfNthOccurrence(const char needle, const std::string &haystack, unsigned int n) const
{
    std::string::size_type pos = 0;
    unsigned int occurrences = 0;
    while ((pos = haystack.find(needle,pos)) != std::string::npos) {
        if(++occurrences == n) break;
        ++pos;
    }
    return ++pos;
}



std::ostream& operator<< (std::ostream& os, const CDatabaseEntry& entry)
{
    return entry.print(os);
}



std::ofstream& operator<< (std::ofstream& os, const CDatabaseEntry& entry)
{
    return entry.serialize(os);
}
