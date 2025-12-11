#include "triangle.hpp"

#include <cmath>

namespace {
template <lib::concepts::Scalar T>
double GetTrianglesArea(const lib::geometry::Point<double> &first,
                        const lib::geometry::Point<double> &second) noexcept {
  return 0.5 * std::pow(std::fabs(static_cast<double>(first - second)), 2) *
         std::sin(lib::geometry::Triangle<T>::ANGLE);
}
} // namespace

namespace lib::geometry {

template <concepts::Scalar T> Triangle<T>::Triangle() noexcept = default;

template <concepts::Scalar T> Triangle<T>::Triangle(const Triangle<T> &other) {
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
  }
}

template <concepts::Scalar T>
Triangle<T>::Triangle(Triangle<T> &&other) noexcept {
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    points_[i] = std::move(other.points_[i]);
  }
}

template <concepts::Scalar T>
Triangle<T> &Triangle<T>::operator=(const Triangle<T> &other) {
  if (this != &other) {
    for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
      points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
  }
  return *this;
}

template <concepts::Scalar T>
Triangle<T> &Triangle<T>::operator=(Triangle<T> &&other) noexcept {
  if (this != &other) {
    Triangle<T> temp = std::move(other);
    swap(*this, temp);
  }
  return *this;
}

template <concepts::Scalar T> Triangle<T>::operator double() const noexcept {
  return GetTrianglesArea<T>(*points_[1], *points_[0]);
}

template <concepts::Scalar T> Point<T> Triangle<T>::GetCenter() const noexcept {
  Point<T> point_sum = Point<T>();
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    point_sum += *points_[i];
  }
  return point_sum / static_cast<T>(NUMBER_OF_VERTICES);
}

template <concepts::Scalar T>
void Triangle<T>::Print(std::ostream &ostream) const {
  ostream << "Triangle's vertices: ";
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    ostream << *points_[i];
  }
}

template <concepts::Scalar T> void Triangle<T>::Read(std::istream &istream) {
  Point<T> temp;
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    istream >> temp;
    points_[i] = std::make_unique<Point<T>>(temp);
  }
}

// I assume that all the vercites are always entered in the same order
template <concepts::Scalar T>
bool operator==(const Triangle<T> &first, const Triangle<T> &second) noexcept {
  for (std::size_t i = 0; i < Triangle<T>::NUMBER_OF_VERTICES; ++i) {
    if (*first.points_[i] != *second.points_[i]) {
      return false;
    }
  }
  return true;
}

template <concepts::Scalar T>
bool operator!=(const Triangle<T> &first, const Triangle<T> &second) noexcept {
  return !(first == second);
}

template <concepts::Scalar T>
void swap(Triangle<T> &first, Triangle<T> &second) noexcept {
  for (std::size_t i = 0; i < Triangle<T>::NUMBER_OF_VERTICES; ++i) {
    first.points_[i].swap(second.points_[i]);
  }
}
} // namespace lib::geometry
