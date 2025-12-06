#pragma once

#include <list>
#include "rediska/data-structures/AbstractDataStructure.hpp"
#include "rediska/data-structures/types.hpp"

class ListDataStructure : public AbstractDataStructure {
public:
    ~ListDataStructure() = default;

    std::expected<std::optional<DSValueType>, DSReturnCode> handle(OperationId op, DSValueType data) override;

private:
    std::list<DSValueType> list_;
};
