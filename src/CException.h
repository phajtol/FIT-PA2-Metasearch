//
// Created by Peter Hajtol on 13.5.17.
//

#ifndef METASEARCH_CEXCEPTION_H
#define METASEARCH_CEXCEPTION_H

#include <string>


/**
 * Exception class. Contains string with error description.
 */

class CException {
    public:
    /**
     * Constructor takes string with error description.
     *
     * @param error - error description
     */
    CException(const std::string& error);

    /**
     * Destructor.
     */
    ~CException();

    /**
     * getter
     *
     * @return - error description
     */
    std::string getError() const;


    protected:

    /**
     * Error description
     */
    std::string error;
};


#endif //METASEARCH_CEXCEPTION_H
