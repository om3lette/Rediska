#include <optional>

template<typename T>
class OptionalRef {
private:
    T* ptr_;

public:
    constexpr OptionalRef() noexcept : ptr_(nullptr) {};
    constexpr OptionalRef(std::nullopt_t) noexcept : ptr_(nullptr) {}
    constexpr OptionalRef(T& ref) noexcept : ptr_(std::addressof(ref)) {}
    constexpr OptionalRef(std::reference_wrapper<T> r) noexcept
        : ptr_(std::addressof(r.get())) {}

    constexpr explicit operator bool() const noexcept { return ptr_ != nullptr; }
    constexpr T& operator*() const noexcept { return *ptr_; }
    constexpr T* operator->() const noexcept { return ptr_; }
    constexpr T* get() const noexcept { return ptr_; }
};
