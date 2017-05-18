//
// Created by Peter Hajtol on 10.5.17.
//

#ifndef METASEARCH_CTEXTFILE_H
#define METASEARCH_CTEXTFILE_H

#include "CDatabaseEntry.h"

/**
 * CTextFile is a class that represents text file.
 * CTextFile inherits from abstract class CDatabaseEntry.
 * This class contains following metadata: line count, word count and character count.
 */

class CTextFile : public CDatabaseEntry {

    public:

    /**
     * CTextFile constructor calls parent constructor and then loads metadata into database.
     * Constructor loads line count, word count and character count.
     *
     * @param file - path to file, either relative or absolute
     */
    CTextFile(const std::string &file);

    /**
     * Alternate constructor which takes all metadata and writes them to object.
     * Primary use for this constuctor is when importing database.
     *
     * @param path - absolute path to file on disk
     * @param filename - name of the file
     * @param size - file size in B
     * @param lines - number of lines in file
     * @param words - number of words in file
     * @param chars - number of characters in file
     */
    CTextFile(const std::string& path, const std::string& filename, unsigned int size, unsigned int lines, unsigned int words, unsigned int chars);

    /**
     * Destructor.
     */
    ~CTextFile();

    /**
     * getter
     *
     * @return  - number of lines in the text file
     */
    unsigned int getLines() const;

    /**
     * getter
     *
     * @return - number of words in the text file
     */
    unsigned int getWords() const;

    /**
     * getter
     *
     * @return - number of characters in the text file
     */
    unsigned int getChars() const;


    protected:

    /**
     * Line count in file
     */
    unsigned int lines;

    /**
     * Word count in file
     */
    unsigned int words;

    /**
     * Character count in file
     */
    unsigned int chars;


    private:

    /**
     * Method to print class content to std::ostream given as parameter.
     * Primary use is to display file metadata to cout.
     *
     * @param os - std::ostream to print output to
     * @return - std::ostream from input
     */
    virtual std::ostream& print(std::ostream& os) const;

    /**
     * Method to write class content to std::ofstream given as parameter.
     * Primary use for this method is when exporting database.
     *
     * @param os - std::ofstream to write data to
     * @return - std::ofstream from input
     */
    virtual std::ofstream& serialize(std::ofstream& os) const;

};


#endif //METASEARCH_CTEXTFILE_H
