#pragma once

#include "figure.hpp"
#include "vector.hpp"

namespace lib::geometry {

template <concepts::Scalar T, typename F>
void PrintCenters(std::ostream &ostream,
                  const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>;
template <concepts::Scalar T, typename F>
void PrintAreas(std::ostream &ostream,
                const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>;
template <concepts::Scalar T, typename F>
double GetTotalArea(const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>;
} // namespace lib::geometry

#include "vector_figure.ipp"
