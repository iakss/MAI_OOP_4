#pragma once

#include "concepts.hpp"

#include <iostream>
#include <limits>

namespace lib::geometry {

constexpr double EPS = std::numeric_limits<double>::epsilon();

template <concepts::Scalar T> class Point {
public:
  Point() noexcept;
  Point(T x, T y) noexcept;

  Point &operator+=(const Point &other) noexcept;
  Point &operator-=(const Point &other) noexcept;
  Point &operator*=(const T value) noexcept;
  Point &operator/=(const T value) noexcept;

  template <concepts::Scalar U> operator Point<U>() const noexcept;

  operator double() const noexcept;

  template <concepts::Scalar U>
  friend std::ostream &operator<<(std::ostream &ostream, const Point<U> &point);

  template <concepts::Scalar U>
  friend std::istream &operator>>(std::istream &istream, Point<U> &point);

public:
  T x;
  T y;
};

template <concepts::Scalar T>
Point<T> operator+(const Point<T> &first, const Point<T> &second) noexcept;

template <concepts::Scalar T>
Point<T> operator-(const Point<T> &first, const Point<T> &second) noexcept;

template <concepts::Scalar T>
Point<T> operator*(const Point<T> &point, const T value) noexcept;

template <concepts::Scalar T>
Point<T> operator*(const T value, const Point<T> &point) noexcept;

template <concepts::Scalar T>
Point<T> operator/(const Point<T> &point, const T value) noexcept;

template <concepts::Scalar T>
bool operator==(const Point<T> &first, const Point<T> &second) noexcept;

template <concepts::Scalar T>
bool operator!=(const Point<T> &first, const Point<T> &second) noexcept;

template <concepts::Scalar T>
std::ostream &operator<<(std::ostream &ostream, const Point<T> &point);

template <concepts::Scalar T>
std::istream &operator>>(std::istream &istream, Point<T> &point);
} // namespace lib::geometry

#include "point.ipp"
