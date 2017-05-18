//
// Created by Peter Hajtol on 30.4.17.
//

#ifndef METASEARCH_CUI_H
#define METASEARCH_CUI_H


#include <string>

/**
 * Abstract class to represent various user interfaces.
 */

class CUI {
    public:
    /**
     * Constuctor without parameters.
     */
    CUI();

    /**
     * Destructor.
     */
    virtual ~CUI();


    /**
     * Method called right after initialization.
     * Can be used to welcome user and show basic information.
     */
    virtual void welcome() const = 0;

    /**
     * Method to help user with list of controls.
     */
    virtual void help() const = 0;

};


#endif //METASEARCH_CUI_H
