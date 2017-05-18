//
// Created by Peter Hajtol on 16.5.17.
//

#ifndef METASEARCH_CVIDEO_H
#define METASEARCH_CVIDEO_H


#include "CDatabaseEntry.h"
#include "CMedia.h"

class CVideo : public CMedia {

    public:

    /**
     * Constructor. Takes path to file and loads metadata from given file using MediaInfo library.
     *
     * @param file - path to file on disk, either relative or absolute
     */
    CVideo(const std::string& file);

    /**
     * Alternate constructor which takes all metadata and writes them to object.
     * Primary use for this constructor is when importing database.
     *
     * @param path - path to file's parent directory
     * @param filename - name of the file
     * @param size - size of the file in B
     * @param width - video width
     * @param height - video height
     * @param length - video length in s
     * @param framerate - video framerate
     * @param format - video format
     */
    CVideo(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height, unsigned int length, double framerate, const std::string& format);

    /**
     * Destructor.
     */
    ~CVideo();

    /**
     * getter
     *
     * @return - video length
     */
    unsigned int getLength() const;

    /**
     * getter
     *
     * @return - video framerate
     */
    double getFramerate() const;

    /**
     * getter
     *
     * @return - video format
     */
    std::string getFormat() const;


    protected:

    /**
     * Video lengt in seconds
     */
    unsigned int length;

    /**
     * Video framerate
     */
    double framerate;

    /**
     * Video format
     */
    std::string format;


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


#endif //METASEARCH_CVIDEO_H
