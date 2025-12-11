#include "square.hpp"

#include <cmath>

namespace {
double GetSquaresArea(const lib::geometry::Point<double> &first,
                      const lib::geometry::Point<double> &second) noexcept {
  return std::pow(std::fabs(static_cast<double>(first - second)), 2);
}
} // namespace

namespace lib::geometry {

template <concepts::Scalar T> Square<T>::Square() noexcept = default;

template <concepts::Scalar T> Square<T>::Square(const Square<T> &other) {
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
  }
}

template <concepts::Scalar T> Square<T>::Square(Square<T> &&other) noexcept {
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    points_[i] = std::move(other.points_[i]);
  }
}

template <concepts::Scalar T>
Square<T> &Square<T>::operator=(const Square<T> &other) {
  if (this != &other) {
    for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
      points_[i] = std::make_unique<Point<T>>(*other.points_[i]);
    }
  }
  return *this;
}

template <concepts::Scalar T>
Square<T> &Square<T>::operator=(Square<T> &&other) noexcept {
  if (this != &other) {
    Square<T> temp = std::move(other);
    swap(*this, temp);
  }
  return *this;
}

template <concepts::Scalar T> Square<T>::operator double() const noexcept {
  return GetSquaresArea(*points_[1], *points_[0]);
}

template <concepts::Scalar T> Point<T> Square<T>::GetCenter() const noexcept {
  Point<T> point_sum = Point<T>();
  for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    point_sum += *points_[i];
  }
  return point_sum / static_cast<T>(NUMBER_OF_VERTICES);
}

template <concepts::Scalar T>
void Square<T>::Print(std::ostream &ostream) const {
  ostream << "Square's vertices: ";
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    ostream << *points_[i];
  }
}

template <concepts::Scalar T> void Square<T>::Read(std::istream &istream) {
  Point<T> temp;
  for (std::size_t i = 0; i < NUMBER_OF_VERTICES; ++i) {
    istream >> temp;
    points_[i] = std::make_unique<Point<T>>(temp);
  }
}

// I assume that all the vercites are always entered in the same order
template <concepts::Scalar T>
bool operator==(const Square<T> &first, const Square<T> &second) noexcept {
  for (std::size_t i = 0; i < Square<T>::NUMBER_OF_VERTICES; ++i) {
    if (*first.points_[i] != *second.points_[i]) {
      return false;
    }
  }
  return true;
}

template <concepts::Scalar T>
bool operator!=(const Square<T> &first, const Square<T> &second) noexcept {
  return !(first == second);
}

template <concepts::Scalar T>
void swap(Square<T> &first, Square<T> &second) noexcept {
  for (std::size_t i = 0; i < Square<T>::NUMBER_OF_VERTICES; ++i) {
    first.points_[i].swap(second.points_[i]);
  }
}
} // namespace lib::geometry
