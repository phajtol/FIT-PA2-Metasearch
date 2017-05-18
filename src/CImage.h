//
// Created by Peter Hajtol on 11.5.17.
//

#ifndef METASEARCH_CIMAGE_H
#define METASEARCH_CIMAGE_H

#include "CMedia.h"

/**
 * Abstract class CImage represents image file.
 * It inherits from CDatabaseEntry and has classes CJPEGImage and CPNGImage inherit from it.
 */
class CImage : public CMedia {

    public:

    /**
     * Constructor takes one parameter, which is path to file.
     * @param file - path to file on the disk, either relative or absolute
     */
    CImage(const std::string& file);

    /**
     * Alternate constructor which takes all the data and writes them to object.
     * Primary use for this constructor is when importing database.
     * @param path - absolute path to file
     * @param filename - name of the file
     * @param size - file size in B
     * @param width - image width
     * @param height - image height
     */
    CImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height);

    /**
     * Destructor.
     */
    virtual ~CImage();



    private:

    /**
     * Virtual print method which is used to show image information to std::ostream.
     * Primary use for this method is printing image info to cout.
     * @param os - reference to std::ostream to write info to
     * @return - reference to std::ostream from input
     */
    virtual std::ostream& print(std::ostream& os) const = 0;

    /**
     * Virtual method which writes image information to std::ofstream.
     * Primary use for this method is writing database to file.
     * @param os
     * @return
     */
    virtual std::ofstream& serialize(std::ofstream& os) const = 0;

};


#endif //METASEARCH_CIMAGE_H
