#pragma once

#include <initializer_list>
#include <memory>

namespace lib::vector {

const std::size_t DEFAULT_CAPACITY = 10;

template <typename T> class Vector {
public:
  Vector() noexcept;
  Vector(std::size_t count);
  Vector(std::size_t count, const T &value);
  Vector(const std::initializer_list<T> &init);

  Vector(const Vector &other);
  Vector &operator=(const Vector &other);
  Vector(Vector &&other) noexcept;
  Vector &operator=(Vector &&other) noexcept;

  ~Vector();

  T &operator[](std::size_t pos) noexcept;
  const T &operator[](std::size_t pos) const noexcept;

  T &Front() noexcept;
  const T &Front() const noexcept;
  T &Back() noexcept;
  const T &Back() const noexcept;
  T *Data() noexcept;
  const T *Data() const noexcept;

  bool Empty() const noexcept;
  std::size_t Size() const noexcept;
  void Reserve(const std::size_t new_cap);
  std::size_t Capacity() const noexcept;

  void Clear() noexcept;
  template <typename U> void Insert(std::size_t pos, U &&value);
  void Erase(std::size_t pos);
  template <typename U> void PushBack(U &&value);
  template <typename... Args> void EmplaceBack(Args &&...args);
  void PopBack() noexcept;

  void Swap(Vector &other) noexcept;
  template <typename U>
  friend void swap(Vector<U> &first, Vector<U> &second) noexcept;

private:
  std::size_t capacity_;
  std::size_t size_;
  std::shared_ptr<T[]> data_;
};
} // namespace lib::vector

#include "vector.ipp"
