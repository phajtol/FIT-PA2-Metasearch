//
// Created by Peter Hajtol on 30.4.17.
//

#ifndef METASEARCH_CDATABASEENTRY_H
#define METASEARCH_CDATABASEENTRY_H


#include <string>


/**
 * Class CDatabaseEntry is an abstract class to represent various types of file types indexed by Metasearch.
 */

class CDatabaseEntry {

    public:

    /**
     * CDatabaseEntry constructor.
     *
     * @param file - path to file on disk, either absolute or relative
     */
    CDatabaseEntry(const std::string& file);

    /**
     * Alternate constructor, which takes path to file's folder and file name and writes them to object.
     * Primary use for this constructor is when importing database entry.
     *
     * @param path - absolute path to file's folder
     * @param filename - name of the file
     * @param size - file size in B
     */
    CDatabaseEntry(const std::string& path, const std::string& filename, unsigned int size);

    /**
     * Destructor.
     */
    virtual ~CDatabaseEntry();

    /**
     * getter
     *
     * @return - name of the file
     */
    std::string getFileName() const;

    /**
     * getter
     *
     * @return - absolute path to file's folder
     */
    std::string getPath() const;

    /**
     * getter
     *
     * @return - file size in B
     */
    unsigned int getSize() const;

    /**
     * operator << overload for std::ostream, primary for printing CDatabaseEntry to std::cout
     * uses CDatabaseEntry::print()
     *
     * @param os - std::ostream to print to
     * @param entry - CDatabaseEntry instance or its child to be written
     * @return - reference to std::ostream given as first parameter
     */
    friend std::ostream& operator<< (std::ostream& os, const CDatabaseEntry& entry);

    /**
     * operator << overload for std::ofstream, primary for writing CDatabaseEntry to file
     * uses CDatabaseEntry::serialize()
     *
     * @param os - std::ofstream to write to
     * @param entry - CDatabaseEntry instance or its child to be written
     * @return - reference to std::ofstream given as first parameter
     */
    friend std::ofstream& operator<< (std::ofstream& os, const CDatabaseEntry& entry);


    protected:

    /**
     * File name with extension
     */
    std::string fileName;

    /**
     * Path to file's parent directory
     */
    std::string path;

    /**
     * File size in B
     */
    unsigned int size;


    private:

    /**
     * Prints indexed metadata to ostream given to the function.
     * Primary use: printing file info to std::cout.
     *
     * @param os - std::ostream to which should content be written
     * @return - reference to std::ostream given to the function as input parameter
     */
    virtual std::ostream& print(std::ostream& os) const = 0;

    /**
     * Writes indexed metadata to output file stream given to the function.
     *
     * Primary use: database export.
     * @param os - std::ofstream to write data to
     * @return - reference to std::ofstream given to the function as input parameter
     */
    virtual std::ofstream& serialize(std::ofstream& os) const = 0;

    /**
     * Function that count occurenced of substring in a string
     *
     * @param needle - substring
     * @param haystack - main string
     * @return - number of occurences of needle in haystack
     */
    unsigned int substringOccurrences (const std::string& needle, const std::string& haystack) const;

    /**
     * Function that returns position of N-th occurence of char in a string, where N is given as input
     *
     * @param needle - char its position will be returned
     * @param haystack - string, in which function searches
     * @param n - number of occurence's position
     * @return - position of N-th occurence of needle in haystack
     */
    std::string::size_type positionOfNthOccurrence (const char needle, const std::string& haystack, unsigned int n) const;
};


#endif //METASEARCH_CDATABASEENTRY_H
