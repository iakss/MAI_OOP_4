#pragma once

#include "figure.hpp"

#include <memory>

namespace lib::geometry {

template <concepts::Scalar T> class Square : public Figure<T> {
public:
  static constexpr std::size_t NUMBER_OF_VERTICES = 4;

  Square() noexcept;

  Square(const Square &other);
  Square(Square &&other) noexcept;

  Square &operator=(const Square &other);
  Square &operator=(Square &&other) noexcept;

  explicit operator double() const noexcept final;

  Point<T> GetCenter() const noexcept final;

  virtual void Print(std::ostream &ostream) const final;
  virtual void Read(std::istream &istream) final;

  template <concepts::Scalar U>
  friend bool operator==(const Square<U> &first,
                         const Square<U> &second) noexcept;

  template <concepts::Scalar U>
  friend bool operator!=(const Square<U> &first,
                         const Square<U> &second) noexcept;

  template <concepts::Scalar U>
  friend void swap(Square<U> &first, Square<U> &second) noexcept;

private:
  std::unique_ptr<Point<T>> points_[NUMBER_OF_VERTICES];
};

template <concepts::Scalar T>
bool operator==(const Square<T> &first, const Square<T> &second) noexcept;

template <concepts::Scalar T>
bool operator!=(const Square<T> &first, const Square<T> &second) noexcept;

template <concepts::Scalar T>
void swap(Square<T> &first, Square<T> &second) noexcept;
} // namespace lib::geometry

#include "square.ipp"
