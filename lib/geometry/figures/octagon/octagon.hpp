#pragma once

#include "figure.hpp"

#include <memory>

namespace lib::geometry {

template <concepts::Scalar T> class Octagon : public Figure<T> {
public:
  static constexpr std::size_t NUMBER_OF_VERTICES = 8;

  Octagon() noexcept;

  Octagon(const Octagon &other);
  Octagon(Octagon &&other) noexcept;

  Octagon &operator=(const Octagon &other);
  Octagon &operator=(Octagon &&other) noexcept;

  explicit operator double() const noexcept final;

  Point<T> GetCenter() const noexcept final;

  virtual void Print(std::ostream &ostream) const final;
  virtual void Read(std::istream &istream) final;

  template <concepts::Scalar U>
  friend bool operator==(const Octagon<U> &first,
                         const Octagon<U> &second) noexcept;

  template <concepts::Scalar U>
  friend bool operator!=(const Octagon<U> &first,
                         const Octagon<U> &second) noexcept;

  template <concepts::Scalar U>
  friend void swap(Octagon<U> &first, Octagon<U> &second) noexcept;

private:
  std::unique_ptr<Point<T>> points_[NUMBER_OF_VERTICES];
};

template <concepts::Scalar T>
bool operator==(const Octagon<T> &first, const Octagon<T> &second) noexcept;

template <concepts::Scalar T>
bool operator!=(const Octagon<T> &first, const Octagon<T> &second) noexcept;

template <concepts::Scalar T>
void swap(Octagon<T> &first, Octagon<T> &second) noexcept;
} // namespace lib::geometry

#include "octagon.ipp"
