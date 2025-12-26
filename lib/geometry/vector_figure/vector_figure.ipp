#include "vector_figure.hpp"

namespace lib::geometry {

template <concepts::Scalar T, typename F>
void PrintCenters(std::ostream &ostream,
                  const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>
{
  ostream << "Centers" << std::endl;
  if constexpr (std::is_pointer_v<F>) {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      ostream << "Figure " << i << ": " << figures[i]->GetCenter() << std::endl;
    }
  } else {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      ostream << "Figure " << i << ": " << figures[i].GetCenter() << std::endl;
    }
  }
}

template <concepts::Scalar T, typename F>
void PrintAreas(std::ostream &ostream,
                const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>
{
  ostream << "Areas" << std::endl;
  if constexpr (std::is_pointer_v<F>) {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      ostream << "Figure " << i << ": " << static_cast<double>(*figures[i])
              << std::endl;
    }
  } else {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      ostream << "Figure " << i << ": " << static_cast<double>(figures[i])
              << std::endl;
    }
  }
}

template <concepts::Scalar T, typename F>
double GetTotalArea(const vector::Vector<F> &figures) noexcept
  requires std::derived_from<std::remove_pointer_t<F>, Figure<T>>
{
  double area = 0.0;
  if constexpr (std::is_pointer_v<F>) {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      area += static_cast<double>(*figures[i]);
    }
  } else {
    for (std::size_t i = 0; i < figures.Size(); ++i) {
      area += static_cast<double>(figures[i]);
    }
  }
  return area;
}
} // namespace lib::geometry
