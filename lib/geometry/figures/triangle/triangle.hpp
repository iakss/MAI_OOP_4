#pragma once

#include "figure.hpp"

#include <memory>
#include <numbers>

namespace lib::geometry {

constexpr double PI = std::numbers::pi;

template <concepts::Scalar T> class Triangle : public Figure<T> {
public:
  static constexpr std::size_t NUMBER_OF_VERTICES = 3;
  static constexpr double ANGLE = PI / 3;

  Triangle() noexcept;

  Triangle(const Triangle &other);
  Triangle(Triangle &&other) noexcept;

  Triangle &operator=(const Triangle &other);
  Triangle &operator=(Triangle &&other) noexcept;

  explicit operator double() const noexcept final;

  Point<T> GetCenter() const noexcept final;

  virtual void Print(std::ostream &ostream) const final;
  virtual void Read(std::istream &istream) final;

  template <concepts::Scalar U>
  friend bool operator==(const Triangle<U> &first,
                         const Triangle<U> &second) noexcept;

  template <concepts::Scalar U>
  friend bool operator!=(const Triangle<U> &first,
                         const Triangle<U> &second) noexcept;

  template <concepts::Scalar U>
  friend void swap(Triangle<U> &first, Triangle<U> &second) noexcept;

private:
  std::unique_ptr<Point<T>> points_[NUMBER_OF_VERTICES];
};

template <concepts::Scalar T>
bool operator==(const Triangle<T> &first, const Triangle<T> &second) noexcept;

template <concepts::Scalar T>
bool operator!=(const Triangle<T> &first, const Triangle<T> &second) noexcept;

template <concepts::Scalar T>
void swap(Triangle<T> &first, Triangle<T> &second) noexcept;
} // namespace lib::geometry

#include "triangle.ipp"
