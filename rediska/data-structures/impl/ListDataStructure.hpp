#pragma once

#include <list>
#include "rediska/data-structures/AbstractDataStructure.hpp"
#include "rediska/data-structures/types.hpp"

class ListDataStructure : public AbstractDataStructure {
public:
    ~ListDataStructure() = default;

    std::expected<std::optional<DSValue>, DSReturnCode> handle(OperationId op, DSValue data) override;

private:
    std::list<DSValue> list_;
};
