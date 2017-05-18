//
// Created by Peter Hajtol on 13.5.17.
//

#include "CException.h"



CException::CException(const std::string &error)
    :
    error(error)
{
}



CException::~CException()
{
}



std::string CException::getError() const
{
    return error;
}