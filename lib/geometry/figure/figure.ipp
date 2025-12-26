#include "figure.hpp"

namespace lib::geometry {

template <concepts::Scalar T>
std::ostream &operator<<(std::ostream &ostream, const Figure<T> &figure) {
  figure.Print(ostream);
  return ostream;
}

template <concepts::Scalar T>
std::istream &operator>>(std::istream &istream, Figure<T> &figure) {
  figure.Read(istream);
  return istream;
}
} // namespace lib::geometry
