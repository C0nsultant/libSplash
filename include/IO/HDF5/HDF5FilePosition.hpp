#pragma once


#include "H5Cpp.h"

#include "../AbstractFilePosition.hpp"


struct HDF5FilePosition : public AbstractFilePosition
{
    HDF5FilePosition(std::string const& s)
            : location{s}
    { }

    std::string location;
};  //HDF5FilePosition
