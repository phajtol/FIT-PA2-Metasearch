#include <iostream>
#include "CCLI.h"
#include "constants.h"


/**
 \mainpage Metasearch documentation

 Metasearch is a simple command-line interface program that loads various file types, stores its metadata and allows you to search files by those metadata.

 \section usage Usage
 Metasearch utilizes bash-like interface. It is controlled via commands. Comprehensive list of commands is written below.

    \subsection commands Commands
    \li "add path-to-file" - adds file to the database, path can be either relative or absolute

    \li "import path-to-file" - imports database from file, path can be either relative or absolute

    \li "export path-to-file" - exports database to the file, path can be either relative or absolute

    \li "search type attribute value" - searches database for files of "type", which have "attribute" equal to "value"

    \li "help" - shows list of all commands with brief description

    \li "exit" - exits the Metasearch and discards any unexported changes in database

 \section file-support File support
 Metasearch supports these files:
    \li images: .jpg, .png
    \li text files: .txt
    \li videos: .mp4, .mov, .avi, .mkv

 \section search Search
    When searching, you can search by file type or optionally by file attribute and value of that attribute. File type is required, attribute and value are optional. If not provided, Metasearch searches for all files of given type <br>
	Recognised types are:
        \li all
        \li video
        \li image
        \li jpg
        \li png
        \li txt
	\subsection recognised-attributes Recognised attributes
    recognised attributes are:
		\li "name", "path", "size" for all types
		\li "width", "height" for types: video, image, jpg, png
		\li "make", "model", "latitude", "longitude" for type jpg
		\li "length", "framerate", "format" for type video
		\li "lines", "words", "chars" for type txt
	\subsection examples Examples:
		\li "search image width 1920" - searches for all images, that have width equal to 1920
		\li "search jpg" - searches for all jpg images
		\li "search all" - shows all files in database

*/


int main(){
    std::string buffer;
    CDatabase db;
    CCLI interface;

    interface.welcome();

    while(true) {
        std::getline(std::cin, buffer);
        if(buffer == METASEARCH_COMMAND_EXIT) break;
        interface.processInput(buffer,db);
    }

    return 0;
}
