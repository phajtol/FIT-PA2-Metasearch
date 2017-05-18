//
// Created by Peter Hajtol on 6.5.17.
//

#ifndef METASEARCH_CJPEGIMAGE_H
#define METASEARCH_CJPEGIMAGE_H


#include "CImage.h"


/**
 * CJPEGImage is a class that represents JPEG image.
 * CJPEGImage inherits from abstract class CDatabaseEntry.
 * This class contains following metadata: width, height, camera make, camera model and GPS coordinates.
 */
class CJPEGImage : public CImage {

    public:

    /**
     * CJPEGImage constructor, calls parent (CDatabaseEntry) constructor and then loads EXIF data from file given as a parameter.
     * CJPEGImage loads image width, height, camera make, camera model and GPS coordinates from file's EXIF data.
     *
     * @param file - either relative or absolute path to file
     */
    CJPEGImage(const std::string& file);

    /**
     * Alternate constructor, which takes all of the metadata and just writes them to object.
     *
     * @param path - absolute path to file on disk
     * @param filename - name of the file
     * @param size - file size in B
     * @param width - image width (from EXIF)
     * @param height - image height (from EXIF)
     * @param make - camera manufacturer (from EXIF)
     * @param model - camera model (from EXIF)
     * @param latitude - GPS latitude (from EXIF)
     * @param longitude - GPS longitude (from EXIF)
     */
    CJPEGImage(const std::string& path, const std::string& filename, unsigned int size, unsigned int width, unsigned int height, const std::string& make, const std::string& model, double latitude, double longitude);

    /**
     * Destructor.
     */
    ~CJPEGImage();

    /**
     * getter
     *
     * @return - camera manufacturer of the image
     */
    std::string getMake() const;

    /**
     * getter
     *
     * @return - camera model of the image
     */
    std::string getModel() const;

    /**
     * getter
     *
     * @return - GPS latitude of the image
     */
    double getLatitude() const;

    /**
     * getter
     *
     * @return - GPS longitude of the image
     */
    double getLongitude() const;


    protected:

    /**
     * Camera manufacturer
     */
    std::string make;

    /**
     * Camera model
     */
    std::string model;

    /**
     * GPS latitude
     */
    double latitude;

    /**
     * GPS longitude
     */
    double longitude;


    private:

    /**
     * Method, that prints class content to std::ostream given as parameter.
     * Primary use for this function is displaying file metadata to cout.
     *
     * @param os - std::ostream to write to
     * @return - the std::ostream from input
     */
    std::ostream& print(std::ostream& os) const;

    /**
     * Method, that writes class content to output file stream given as parameter.
     * Primary use for this function is when exporting database.
     *
     * @param os - std::ofstream to write to
     * @return - std::ofstream from input
     */
    std::ofstream& serialize(std::ofstream& os) const;

    /**
     * Private method, that transforms GPS coordinates from C-string as they are retrieved from libexif into double.
     * Method returns false if no GPS coordinates can be found in the C-string, true if coordinates have been successfully transformed.
     * Output parameter is zero, if no transformation has taken place.
     *
     * @param in - C-style string in format "X, Y, Z" where X are degrees, Y are minutes and Z are seconds
     * @param ref - GPS coordinates reference, either "N" or "S" or "E" or "W"
     * @param out - in/out parameter - result GPS coordinate in decimal format
     * @return - TRUE if coordinates were successfully parsed, FALSE if otherwise
     */
    bool parseGPS(const char* in, const char* ref, double* out) const;
};


#endif //METASEARCH_CJPEGIMAGE_H
