// table.hpp
// Definition of a genertic lookup table

template <typename IndexType, typename ValueType>
struct lookupTableItem {
    IndexType index;
    ValueType value;
};


template <typename IndexType, typename ValueType>
class LookupTable
{
public:
    LookupTable(lookupTableItem<IndexType, ValueType> *table) 
            : m_table(table) {
    }

    ~LookupTable() {}

    IndexType GetIndexFromValue(const ValueType value) const {
        // TODO: table lookup on value 
        return static_cast<IndexType>(0);
    }

    ValueType GetValueFromIndex(const IndexType index) const {
        // TODO: table lookup on index
        return static_cast<ValueType>(0);
    }

private:
    lookupTableItem<IndexType, ValueType> *m_table;
};

