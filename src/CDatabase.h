//
// Created by Peter Hajtol on 30.4.17.
//

#ifndef METASEARCH_CDATABASE_H
#define METASEARCH_CDATABASE_H


#include <vector>
#include <memory>
#include "CDatabaseEntry.h"



/**
 * Enum type, which contains file types.
 * Used to determine file types to search for.
 */
enum file_types
{
    ALL,        /**< search all files */
    IMAGE,      /**< search only images */
    IMAGE_JPEG, /**< search only JPEG images */
    IMAGE_PNG,  /**< search only PNG images*/
    VIDEO,      /**< search only videos */
    TEXT_TXT    /**< search only text files */
};


/**
 * Enum type, which is used to determine file attributes to search for.
 */
enum file_attributes
{
    NONE,                       /**< don't search for parameters */
    FILE_FILENAME,              /**< search all files by file name */
    FILE_PATH,                  /**< search all files by path */
    FILE_SIZE,                  /**< search all files by file size */
    IMG_VIDEO_WIDTH,            /**< search for height in videos and images */
    IMG_VIDEO_HEIGHT,           /**< search for width in videos and images */
    IMAGE_JPEG_MAKE,            /**< search for camera manufacturer in JPEG images */
    IMAGE_JPEG_MODEL,           /**< search for camera model in JPEG images */
    IMAGE_JPEG_GPS_LATITUDE,    /**< search for GPS longitude in JPEG images */
    IMAGE_JPEG_GPS_LONGITUDE,   /**< search for GPS longitude in JPEG images */
    VIDEO_LENGTH,               /**< search for video length in video files */
    VIDEO_FRAMERATE,            /**< search for video framerate in video files */
    VIDEO_FORMAT,               /**< search for video format in video files */
    TEXT_LINES,                 /**< search for line count in text files */
    TEXT_WORDS,                 /**< search for word count in text files */
    TEXT_CHARS                  /**< search for character count in text files */
};


/**
 * Class CDatabase represents Metasearch database.
 * CDatabase allows adding and searching files as well as its export and import.
 */

class CDatabase {
    public:

    /**
     * Constructor.
     */
    CDatabase();

    /**
     * Destructor.
     */
    ~CDatabase();

    /**
     * Adds file to the database.
     *
     * @param file - path to file on disk, either relative or absolute
     * @throw CException - if input file cannot be read or if it has unsupported extenstion
     */
    void add(const std::string& file);

    /**
     * Exports database content to text file on disk.
     *
     * @param file - path to export file on disk, either relative or absolute
     * @throw CException - if specified file cannot be written to
     */
    void exportDB(const std::string& file) const;

    /**
     * Imports previously exported database from text file on disk.
     * If import file contains line that doesn't match Metasearch's format, that line will be ignored.
     *
     * @param file - path to import file on disk, either relative or absolute
     * @throw CException - if input fail cannot be read
     */
    void import(const std::string& file);

    /**
     * Searches the database.
     *
     * @param fileType - enum type, which specifies which files to search for
     * @param fileAttribute - enum type, which specifies what attributes to search for (optional)
     * @param needle - std::string, value of the fileAttribute to search for (optional, required if fileAttribute is given)
     * @return - std::vector of std::shared_ptrs to database entries that match given criteria
     */
    std::vector<std::shared_ptr<CDatabaseEntry> > search(file_types fileType, file_attributes fileAttribute = NONE, const std::string& needle = "") const;


    protected:
    /**
     * Contains file objects with metadata.
     */
    std::vector< std::shared_ptr<CDatabaseEntry> > data;

    private:
    /**
     * Function checks if CDatabaseEntry is of given type.
     *
     * @param fileType - enum type, which specifies type of file we want
     * @param entry - std::shared_ptr to entry in database
     * @return - TRUE if given entry is of given type, FALSE if not
     */
    bool isFileType(file_types fileType, std::shared_ptr<CDatabaseEntry> entry) const;

};


#endif //METASEARCH_CDATABASE_H
