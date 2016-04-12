/**
 * Copyright 2013 Felix Schmitt
 *           2015 Carlchristian Eckert
 *
 * This file is part of libSplash.
 *
 * libSplash is free software: you can redistribute it and/or modify
 * it under the terms of of either the GNU General Public License or
 * the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libSplash is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License and the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * and the GNU Lesser General Public License along with libSplash.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BASETYPES_ARRAY_HPP
#define BASETYPES_ARRAY_HPP

#include <stdint.h>
#include <string>

#include "splash/CollectionType.hpp"

namespace splash
{

#define TYPE_ARRAY(_name, _h5_type, _real_type, _size)                         \
    class ColType##_name##Array : public CollectionType                        \
    {                                                                          \
    public:                                                                    \
                                                                               \
        ColType##_name##Array()                                                \
        {                                                                      \
            const hsize_t dim[] = {_size};                                     \
            this->type = H5Tarray_create(_h5_type, 1, dim);                    \
        }                                                                      \
                                                                               \
        ~ColType##_name##Array()                                               \
        { H5Tclose(this->type); }                                              \
                                                                               \
        size_t getSize() const                                                 \
        { return sizeof (_real_type) * _size; }                                \
                                                                               \
        static CollectionType* genType(hid_t datatype_id)                      \
        {                                                                      \
            bool found = false;                                                \
            H5T_class_t h5_class = H5Tget_class(datatype_id);                  \
            if(h5_class == H5T_ARRAY)                                          \
            {                                                                  \
                hid_t base = H5Tget_super(datatype_id);                        \
                if(H5Tequal(base, _h5_type) == 1)                              \
                {                                                              \
                    if(H5Tget_array_ndims(datatype_id) == 1)                   \
                    {                                                          \
                        hsize_t adims_out[1];                                  \
                        H5Tget_array_dims(datatype_id, adims_out);             \
                        if(adims_out[0] == _size)                              \
                            found = true;                                      \
                    }                                                          \
                }                                                              \
                H5Tclose(base);                                                \
            }                                                                  \
            if(found)                                                          \
                return new ColType##_name##Array;                              \
            else                                                               \
                return NULL;                                                   \
        }                                                                      \
                                                                               \
        std::string toString() const                                           \
        {                                                                      \
            return #_name"Array";                                              \
        }                                                                      \
    };

TYPE_ARRAY(Float2, H5T_NATIVE_FLOAT, float, 2);
TYPE_ARRAY(Float3, H5T_NATIVE_FLOAT, float, 3);
TYPE_ARRAY(Float4, H5T_NATIVE_FLOAT, float, 4);

TYPE_ARRAY(Double2, H5T_NATIVE_DOUBLE, double, 2);
TYPE_ARRAY(Double3, H5T_NATIVE_DOUBLE, double, 3);
TYPE_ARRAY(Double4, H5T_NATIVE_DOUBLE, double, 4);

TYPE_ARRAY(Int2, H5T_NATIVE_INT, int, 2);
TYPE_ARRAY(Int3, H5T_NATIVE_INT, int, 3);
TYPE_ARRAY(Int4, H5T_NATIVE_INT, int, 4);
}

#endif /* BASETYPES_ARRAY_HPP */
