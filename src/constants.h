//
// Created by Peter Hajtol on 11.5.17.
//

#ifndef METASEARCH_CONSTANTS_H
#define METASEARCH_CONSTANTS_H

#include <string>

/**
 * Constans used throughout the program, e.g. commands or errors.
 */

static const char           METASEARCH_OUTPUT_LEADING_CHAR  = '#';
static const char           METASEARCH_FILE_OUTPUT_LEADING_CHAR  = '-';

static const char           METASEARCH_EXPORT_DELIMETER     = '|';



static const std::string    METASEARCH_COMMAND_ADD      = "add";
static const std::string    METASEARCH_COMMAND_HELP     = "help";
static const std::string    METASEARCH_COMMAND_EXIT     = "exit";
static const std::string    METASEARCH_COMMAND_IMPORT   = "import";
static const std::string    METASEARCH_COMMAND_EXPORT   = "export";
static const std::string    METASEARCH_COMMAND_SEARCH   = "search";

static const std::string    METASEARCH_ERROR_PARAMETER_NONE         = "No parameter given.";
static const std::string    METASEARCH_ERROR_PARAMETER_INVALID      = "Invalid parameter";
static const std::string    METASEARCH_ERROR_COMMAND_NONE           = "Please enter command. Use \"" + METASEARCH_COMMAND_HELP + "\" to show list of all commands.";
static const std::string    METASEARCH_ERROR_COMMAND_INVALID        = "Invalid command. Use \"" + METASEARCH_COMMAND_HELP + "\" to show list of all commands.";
static const std::string    METASEARCH_ERROR_EXPORT_FILE_FAIL       = "There is an error with the output file you specified.";
static const std::string    METASEARCH_ERROR_IMPORT_FILE_FAIL       = "There is an error with the import file you specified.";
static const std::string    METASEARCH_ERROR_UNSUPPORTED_EXTENSION  = "Unsupported file extension";
static const std::string    METASEARCH_ERROR_FILE_READING           = "There is a problem with reading file ";

static const std::string    METASEARCH_SUCCESS_ADD      = "File has been added.";
static const std::string    METASEARCH_SUCCESS_IMPORT   = "Database has been successfully imported.";
static const std::string    METASEARCH_SUCCESS_EXPORT   = "Database has been successfully exported.";

static const std::string    METASEARCH_EXPORT_TAG_PNG   = "PNG";
static const std::string    METASEARCH_EXPORT_TAG_JPG   = "JPG";
static const std::string    METASEARCH_EXPORT_TAG_TXT   = "TXT";
static const std::string    METASEARCH_EXPORT_TAG_VIDEO = "VID";

static const std::string    METASEARCH_FILE_EXTENSION_JPEG      = "jpg";
static const std::string    METASEARCH_FILE_EXTENSION_PNG       = "png";
static const std::string    METASEARCH_FILE_EXTENSION_TXT       = "txt";
static const std::string    METASEARCH_FILE_EXTENSION_VIDEO_1   = "mov";
static const std::string    METASEARCH_FILE_EXTENSION_VIDEO_2   = "mp4";
static const std::string    METASEARCH_FILE_EXTENSION_VIDEO_3   = "mkv";
static const std::string    METASEARCH_FILE_EXTENSION_VIDEO_4   = "avi";

static const std::string    METASEARCH_FILE_ATTRIBUTE_NAME   = "name";
static const std::string    METASEARCH_FILE_ATTRIBUTE_PATH   = "path";
static const std::string    METASEARCH_FILE_ATTRIBUTE_SIZE   = "size";
static const std::string    METASEARCH_FILE_ATTRIBUTE_WIDTH  = "width";
static const std::string    METASEARCH_FILE_ATTRIBUTE_HEIGHT = "height";
static const std::string    METASEARCH_FILE_ATTRIBUTE_MAKE   = "make";
static const std::string    METASEARCH_FILE_ATTRIBUTE_MODEL  = "model";
static const std::string    METASEARCH_FILE_ATTRIBUTE_LAT    = "latitude";
static const std::string    METASEARCH_FILE_ATTRIBUTE_LONG   = "longitude";
static const std::string    METASEARCH_FILE_ATTRIBUTE_LENGTH = "length";
static const std::string    METASEARCH_FILE_ATTRIBUTE_FRAMES = "framerate";
static const std::string    METASEARCH_FILE_ATTRIBUTE_FORMAT = "format";
static const std::string    METASEARCH_FILE_ATTRIBUTE_LINES  = "lines";
static const std::string    METASEARCH_FILE_ATTRIBUTE_WORDS  = "words";
static const std::string    METASEARCH_FILE_ATTRIBUTE_CHARS  = "characters";

static const std::string    METASEARCH_SEARCH_RESULTS_COUNT_SG  = "result found";
static const std::string    METASEARCH_SEARCH_RESULTS_COUNT_PL  = "results found";

static const unsigned int   METASEARCH_EXIF_BUFFER_SIZE = 100;

#endif //METASEARCH_CONSTANTS_H
