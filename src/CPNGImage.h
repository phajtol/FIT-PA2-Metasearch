//
// Created by Peter Hajtol on 7.5.17.
//

#ifndef METASEARCH_CPNGIMAGE_H
#define METASEARCH_CPNGIMAGE_H


#include "CImage.h"

/**
 * CPNGImage is a class that represents PNG image.
 * CPNGImage inherits from abstract class CImage.
 * This class contains following metadata: width and height.
 */

class CPNGImage : public CImage {

    public:

    /**
     * CPNGImage constructor, loads data from file given as a parameter.
     * Loads image width and height by opening file and reading specific bytes.
     *
     * @param file - either relative or absolute path to file
     */
    CPNGImage(const std::string &file);

    /**
     * Alternate constructor which takes all metadata and writes them to object.
     * Primary use for this constructor is when importing database.
     *
     * @param path - path to parent's directory
     * @param filename - name of the file
     * @param size - file size in B
     * @param width - image width
     * @param height - image height
     */
    CPNGImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height);

    /**
     * Destructor.
     */
    ~CPNGImage();


    private:

    /**
    * Method, that prints class content to std::ostream given as parameter.
    * Primary use for this function is displaying file metadata to cout.
     *
    * @param os - std::ostream to write to
    * @return - the std::ostream from input
    */
    virtual std::ostream& print(std::ostream& os) const;

    /**
     * Method, that writes class content to output file stream given as parameter.
     * Primary use for this function is when exporting database.
     *
     * @param os - std::ofstream to write to
     * @return - std::ofstream from input
     */
    virtual std::ofstream& serialize(std::ofstream& os) const;

};


#endif //METASEARCH_CPNGIMAGE_H
