#pragma once

#include <expected>
#include <optional>
#include "rediska/common/enums.hpp"
#include "rediska/data-structures/DSReturnCode.hpp"
#include "rediska/data-structures/types.hpp"

class AbstractDataStructure {
public:
    virtual ~AbstractDataStructure() = default;

    virtual std::expected<std::optional<DSValue>, DSReturnCode> handle(OperationId op, DSValue data) = 0;
};
