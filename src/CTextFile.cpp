//
// Created by Peter Hajtol on 10.5.17.
//

#include <iostream>
#include <fstream>
#include "CTextFile.h"
#include "constants.h"


CTextFile::CTextFile(const std::string &file) : CDatabaseEntry(file)
{
    std::string line;
    std::ifstream inputFile(file);

    lines = words = chars = 0;

    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            ++lines;
            chars += line.length();
            for(std::string::const_iterator i = line.begin(); i != line.end(); ++i)
                if(!isalnum(*i))
                    ++words;
        }
    }
}



CTextFile::CTextFile(const std::string& path, const std::string& filename, unsigned int size, unsigned int lines, unsigned int words,
                     unsigned int chars)
        :
        CDatabaseEntry(path,filename,size),
        lines(lines),
        words(words),
        chars(chars)
{
}



CTextFile::~CTextFile()
{

}



std::ostream& CTextFile::print(std::ostream &os) const
{
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_NAME << ": " << fileName << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_PATH << ": " << path << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_SIZE << ": " << size << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_LINES << ": " << lines << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_WORDS << ": " << words << std::endl;
    os << METASEARCH_FILE_OUTPUT_LEADING_CHAR << " " << METASEARCH_FILE_ATTRIBUTE_CHARS << ": " << chars << std::endl;
    return os;
}



std::ofstream& CTextFile::serialize(std::ofstream &os) const
{
    os << METASEARCH_EXPORT_TAG_TXT
       << METASEARCH_EXPORT_DELIMETER << path
       << METASEARCH_EXPORT_DELIMETER << fileName
       << METASEARCH_EXPORT_DELIMETER << size
       << METASEARCH_EXPORT_DELIMETER << lines
       << METASEARCH_EXPORT_DELIMETER << words
       << METASEARCH_EXPORT_DELIMETER << chars;
    return os;
}



unsigned int CTextFile::getLines() const
{
    return lines;
}



unsigned int CTextFile::getWords() const
{
    return words;
}



unsigned int CTextFile::getChars() const
{
    return chars;
}
