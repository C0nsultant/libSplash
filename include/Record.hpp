#pragma once


#include <memory>

#include <boost/variant.hpp>

#include "Attributable.hpp"
#include "RecordComponent.hpp"

class Record : public Attributable
{
    friend class Mesh;
    friend class HDF5Writer;
public:
    enum class Dimension : size_t
    {
        one = 1, two, three
    };

    enum class UnitDimension : size_t
    {
        L = 0, M, T, I, theta, N, J
    };

    static Record makeTensorRecord(Dimension, std::initializer_list< std::string >);
    static Record makeVectorRecord(std::initializer_list< std::string >);
    static Record makeScalarRecord(Record::Dimension rd);
    static Record makeConstantRecord(Dimension, std::initializer_list< int >, std::initializer_list< std::string >);

    Record(Dimension dim, std::initializer_list< std::string > comps, bool isRecordComponent = false);
    Record(Record const &);

    std::array< double, 7 > unitDimension() const;
    Record& setUnitDimension(std::map< Record::UnitDimension, double > const &);

    float timeOffset() const;
    Record& setTimeOffset(float const);

    RecordComponent& operator[](std::string const&);

    RecordComponent scalar;

protected:
    std::map< std::string, RecordComponent > m_components;
    bool m_isComponent;
    Dimension m_dimension;
};  //Record
