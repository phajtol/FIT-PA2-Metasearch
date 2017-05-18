//
// Created by Peter Hajtol on 30.4.17.
//

#ifndef METASEARCH_CCLI_H
#define METASEARCH_CCLI_H


#include "CUI.h"
#include "CDatabase.h"


/**
 * CCLI represents command line interface.
 * Class inherits from abstract user interface class CUI.
 */

class CCLI : public CUI {
    public:
    /**
     * Constructor. Doesn't need any parameters.
     */
    CCLI();

    /**
     * Destructor.
     */
    ~CCLI();

    /**
     * Method parses user's input and if it's correct, executes given command on the database given as parameter.
     * @param in - std::string containing user query
     * @param db - reference to database, on which the command should be executed
     */
    void processInput(const std::string& in, CDatabase& db) const;

    /**
     * Method which welcomes user to program and presents basic info about program.
     */
    void welcome() const;

    /**
     * Method, which shows user various command used to control the program.
     */
    void help() const;

};


#endif //METASEARCH_CCLI_H
