#pragma once

#include "point.hpp"

namespace lib::geometry {

template <concepts::Scalar T> class Figure {
public:
  virtual Point<T> GetCenter() const noexcept = 0;
  virtual operator double() const noexcept = 0;

  virtual ~Figure() noexcept = default;

  virtual void Print(std::ostream &ostream) const = 0;
  virtual void Read(std::istream &istream) = 0;

  template <concepts::Scalar U>
  friend std::ostream &operator<<(std::ostream &ostream,
                                  const Figure<U> &figure);

  template <concepts::Scalar U>
  friend std::istream &operator>>(std::istream &istream, Figure<U> &figure);
};

template <concepts::Scalar T>
std::ostream &operator<<(std::ostream &ostream, const Figure<T> &figure);

template <concepts::Scalar T>
std::istream &operator>>(std::istream &istream, Figure<T> &figure);
} // namespace lib::geometry

#include "figure.ipp"
