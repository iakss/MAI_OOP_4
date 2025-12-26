#include "vector.hpp"

#include <cstring>
#include <type_traits>

namespace lib::vector {

template <typename T>
Vector<T>::Vector() noexcept : capacity_(0), size_(0), data_(nullptr) {}

template <typename T>
Vector<T>::Vector(std::size_t count)
    : capacity_(std::max(count, DEFAULT_CAPACITY)), size_(count),
      data_(count > 0 ? std::make_shared<T[]>(count) : nullptr) {}

template <typename T>
Vector<T>::Vector(std::size_t count, const T &value)
    : capacity_(std::max(count, DEFAULT_CAPACITY)), size_(count),
      data_(count > 0 ? std::make_shared<T[]>(count, value) : nullptr) {}

template <typename T>
Vector<T>::Vector(const std::initializer_list<T> &init)
    : capacity_(std::max(init.size(), DEFAULT_CAPACITY)), size_(init.size()),
      data_(init.size() > 0 ? std::make_shared_for_overwrite<T[]>(init.size())
                            : nullptr) {
  std::size_t indx = 0;
  for (const T &i : init) {
    new (data_.get() + indx) T(i);
    ++indx;
  }
}

template <typename T>
Vector<T>::Vector(const Vector &other)
    : capacity_(other.capacity_), size_(other.size_),
      data_(std::make_shared_for_overwrite<T[]>(other.capacity_)) {
  for (std::size_t i = 0; i < size_; ++i) {
    new (data_.get() + i) T(other.data_[i]);
  }
}

template <typename T> Vector<T> &Vector<T>::operator=(const Vector &other) {
  if (this != &other) {
    Vector<T> temp(other);
    swap(*this, temp);
  }
  return *this;
}

template <typename T>
Vector<T>::Vector(Vector &&other) noexcept
    : capacity_(other.capacity_), size_(other.size_),
      data_(std::move(other.data_)) {
  other.capacity_ = 0;
  other.size_ = 0;
  other.data_ = nullptr;
}

template <typename T> Vector<T> &Vector<T>::operator=(Vector &&other) noexcept {
  if (this != &other) {
    Vector<T> temp(std::move(other));
    swap(*this, temp);
  }
  return *this;
}

template <typename T> T &Vector<T>::operator[](std::size_t pos) noexcept {
  return data_[pos];
}

template <typename T>
const T &Vector<T>::operator[](std::size_t pos) const noexcept {
  return data_[pos];
}

template <typename T> T &Vector<T>::Front() noexcept { return data_[0]; }

template <typename T> const T &Vector<T>::Front() const noexcept {
  return data_[0];
}

template <typename T> T &Vector<T>::Back() noexcept { return data_[size_ - 1]; }

template <typename T> const T &Vector<T>::Back() const noexcept {
  return data_[size_ - 1];
}

template <typename T> T *Vector<T>::Data() noexcept { return data_.get(); }

template <typename T> const T *Vector<T>::Data() const noexcept {
  return data_.get();
}

template <typename T> bool Vector<T>::Empty() const noexcept {
  return size_ == 0;
}

template <typename T> std::size_t Vector<T>::Size() const noexcept {
  return size_;
}

template <typename T> void Vector<T>::Reserve(const std::size_t new_cap) {
  if (new_cap > capacity_ or capacity_ == 0) {
    std::size_t to_alloc = std::max(new_cap, DEFAULT_CAPACITY);
    std::shared_ptr<T[]> new_data =
        std::make_shared_for_overwrite<T[]>(to_alloc);
    if constexpr (std::is_trivially_copyable_v<T>) {
      std::memcpy(new_data.get(), data_.get(), sizeof(T) * size_);
    } else {
      std::uninitialized_move(data_.get(), data_.get() + size_, new_data.get());
    }
    capacity_ = to_alloc;
    data_ = std::move(new_data);
  }
}

template <typename T> std::size_t Vector<T>::Capacity() const noexcept {
  return capacity_;
}

template <typename T> void Vector<T>::Clear() noexcept {
  if constexpr (!std::is_trivially_destructible_v<T>) {
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i].~T();
    }
  }
  size_ = 0;
}

template <typename T>
template <typename U>
void Vector<T>::Insert(std::size_t pos, U &&value) {
  if (size_ == capacity_) {
    Reserve(2 * capacity_);
  }
  if constexpr (std::is_trivially_copyable_v<T> and
                std::is_trivially_destructible_v<T>) {
    std::memmove(data_.get() + pos + 1, data_.get() + pos,
                 (size_ - pos) * sizeof(T));
  } else {
    new (data_.get() + size_) T();
    for (std::size_t i = size_; i > pos; --i) {
      data_[i] = std::move(data_[i - 1]);
    }
  }
  data_[pos] = std::forward<U>(value);
  ++size_;
}

template <typename T> void Vector<T>::Erase(std::size_t pos) {
  if constexpr (std::is_trivially_copyable_v<T> and
                std::is_trivially_destructible_v<T>) {
    std::memmove(data_.get() + pos, data_.get() + pos + 1,
                 (size_ - pos - 1) * sizeof(T));
  } else {
    for (std::size_t i = pos; i < size_ - 1; ++i) {
      data_[i] = std::move(data_[i + 1]);
    }
    data_[size_ - 1].~T();
  }
  --size_;
}

template <typename T>
template <typename U>
void Vector<T>::PushBack(U &&value) {
  EmplaceBack(std::forward<U>(value));
}

template <typename T>
template <typename... Args>
void Vector<T>::EmplaceBack(Args &&...args) {
  if (size_ == capacity_) {
    Reserve(2 * capacity_);
  }
  new (data_.get() + size_) T(std::forward<Args>(args)...);
  ++size_;
}

template <typename T> void Vector<T>::PopBack() noexcept {
  if constexpr (!std::is_trivially_destructible_v<T>) {
    Back().~T();
  }
  --size_;
}

template <typename T> Vector<T>::~Vector() {}

template <typename T> void Vector<T>::Swap(Vector &other) noexcept {
  swap(*this, other);
}

template <typename T> void swap(Vector<T> &first, Vector<T> &second) noexcept {
  std::swap(first.capacity_, second.capacity_);
  std::swap(first.size_, second.size_);
  std::swap(first.data_, second.data_);
}
} // namespace lib::vector
