#pragma once

#include <expected>
#include <optional>
#include "rediska/common/enums.hpp"
#include "rediska/data-structures/DSReturnCode.hpp"
#include "rediska/data-structures/types.hpp"

class AbstractDataStructure {
public:
    virtual std::expected<std::optional<DSValueType>, DSReturnCode> handle(OperationId op, DSValueType data) = 0;
};
