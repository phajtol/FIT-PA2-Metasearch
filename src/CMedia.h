//
// Created by Peter Hajtol on 16.5.17.
//

#ifndef METASEARCH_CMEDIA_H
#define METASEARCH_CMEDIA_H


#include "CDatabaseEntry.h"

/**
 * Abstract class which represents media files like images or videos.
 */

class CMedia : public CDatabaseEntry {

    public:

    /**
     * Constructor.
     *
     * @param file - path to file, either absolute or relative
     */
    CMedia(const std::string& file);

    /**
     * Alternate constructor which takes all metadata and writes them into object.
     * Primary use for this constructor is when importing database.
     *
     * @param path - path to file
     * @param filename - file name
     * @param size - file size in B
     * @param width - media width
     * @param height - media height
     */
    CMedia(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height);

    /**
     * Destructor.
     */
    virtual ~CMedia();

    /**
     * getter
     *
     * @return - media width
     */
    unsigned int getWidth() const;

    /**
     * getter
     *
     * @return - media height
     */
    unsigned int getHeight() const;



    protected:

    /**
     * Image or video width
     */
    unsigned int width;

    /**
     * Image or video height
     */
    unsigned int height;



    private:

    /**
     * Virtual print method which is used to show image information to std::ostream.
     * Primary use for this method is printing image info to cout.
     *
     * @param os - reference to std::ostream to write info to
     * @return - reference to std::ostream from input
     */
    virtual std::ostream& print(std::ostream& os) const = 0;

    /**
     * Virtual method which writes image information to std::ofstream.
     * Primary use for this method is writing database to file.
     *
     * @param os
     * @return
     */
    virtual std::ofstream& serialize(std::ofstream& os) const = 0;
};


#endif //METASEARCH_CMEDIA_H
