#include <list>
#include "rediska/data-structures/AbstractDataStructure.hpp"
#include "rediska/data-structures/DSReturnCode.hpp"
#include "rediska/data-structures/types.hpp"

class ListDataStructure : public AbstractDataStructure {
public:
    ~ListDataStructure() = default;

    using arguments = struct {};

    std::expected<std::optional<DSValue>, DSReturnCode> handle(OperationId op, DSValue data) override {
        switch (op) {
            case OperationId::LIST_GET: {
                // TODO: Index
                // if (index < 0 || index >= list_.size()) {
                //     return std::unexpected(DSReturnCode::OUT_OF_RANGE);
                // }
                return std::make_optional(*list_.begin());
            }
            case OperationId::LIST_SET: {
                *list_.begin() = data;
                return std::nullopt;
            }
            case OperationId::LIST_PUSH_BACK: {
                list_.push_back(data);
                return std::nullopt;
            }
            case OperationId::LIST_POP_BACK: {
                if (list_.empty()) {
                    return std::unexpected(DSReturnCode::EMPTY);
                }
                DSValue value = list_.back();
                list_.pop_back();
                return std::make_optional(value);
            }
            case OperationId::LIST_INSERT: {
                // TODO: if index
                list_.insert(list_.begin(), data);
                return std::nullopt;
            }
            case OperationId::LIST_ERASE: {
                // TODO: if index
                list_.erase(list_.begin());
                return std::nullopt;
            }
            default:
                return std::unexpected(DSReturnCode::INCOMPATIBLE_OPERATION);
        }
    }

private:
    std::list<DSValue> list_;
};
