#include "point.hpp"

#include <cmath>

namespace lib::geometry {

template <concepts::Scalar T> Point<T>::Point() noexcept : x(0), y(0) {}

template <concepts::Scalar T> Point<T>::Point(T x, T y) noexcept : x(x), y(y) {}

template <concepts::Scalar T>
Point<T> &Point<T>::operator+=(const Point<T> &other) noexcept {
  x += other.x;
  y += other.y;
  return *this;
}

template <concepts::Scalar T>
Point<T> &Point<T>::operator-=(const Point<T> &other) noexcept {
  x -= other.x;
  y -= other.y;
  return *this;
}

template <concepts::Scalar T>
Point<T> &Point<T>::operator*=(const T value) noexcept {
  x *= value;
  y *= value;
  return *this;
}

template <concepts::Scalar T>
Point<T> &Point<T>::operator/=(const T value) noexcept {
  x /= value;
  y /= value;
  return *this;
}

template <concepts::Scalar T>
template <concepts::Scalar U>
Point<T>::operator Point<U>() const noexcept {
  return Point<U>(static_cast<U>(x), static_cast<U>(y));
}

template <concepts::Scalar T> Point<T>::operator double() const noexcept {
  return std::sqrt(std::pow(x, 2.0) + std::pow(y, 2.0));
}

template <concepts::Scalar T>
Point<T> operator+(const Point<T> &first, const Point<T> &second) noexcept {
  return Point<T>(first.x + second.x, first.y + second.y);
}

template <concepts::Scalar T>
Point<T> operator-(const Point<T> &first, const Point<T> &second) noexcept {
  return Point<T>(first.x - second.x, first.y - second.y);
}

template <concepts::Scalar T>
Point<T> operator*(const Point<T> &point, const T value) noexcept {
  return Point<T>(value * point.x, value * point.y);
}

template <concepts::Scalar T>
Point<T> operator*(const T value, const Point<T> &point) noexcept {
  return Point<T>(value * point.x, value * point.y);
}

template <concepts::Scalar T>
Point<T> operator/(const Point<T> &point, const T value) noexcept {
  return Point<T>(point.x / value, point.y / value);
}

template <concepts::Scalar T>
bool operator==(const Point<T> &first, const Point<T> &second) noexcept {
  if (std::is_floating_point_v<T>) {
    return std::fabs(static_cast<double>(first - second)) < EPS;
  } else {
    return first.x == second.x && first.y == second.y;
  }
}

template <concepts::Scalar T>
bool operator!=(const Point<T> &first, const Point<T> &second) noexcept {
  return !(first == second);
}

template <concepts::Scalar T>
std::ostream &operator<<(std::ostream &ostream, const Point<T> &point) {
  ostream << "(" << point.x << ", " << point.y << ")";
  return ostream;
}

template <concepts::Scalar T>
std::istream &operator>>(std::istream &istream, Point<T> &point) {
  istream >> point.x >> point.y;
  return istream;
}
} // namespace lib::geometry
