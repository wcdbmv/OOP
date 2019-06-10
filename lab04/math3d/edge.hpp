#ifndef LAB04_MATH3D_EDGE_HPP_
#define LAB04_MATH3D_EDGE_HPP_

#include <istream>
#include <ostream>

class Edge {
 public:
  using reference = std::size_t&;
  using const_reference = const std::size_t&;
  using size_type = std::size_t;

  constexpr explicit Edge(std::size_t p1 = 0, std::size_t p2 = 0);

  constexpr reference p1();
  constexpr const_reference p1() const;
  constexpr reference p2();
  constexpr const_reference p2() const;

  constexpr reference operator[](size_type index);
  constexpr const_reference operator[](size_type index) const;
  inline reference at(size_type index);
  inline const_reference at(size_type index) const;

 private:
  std::size_t p1_, p2_;
};

inline std::istream& operator>>(std::istream& is, Edge& edge);
inline std::ostream& operator<<(std::ostream& os, const Edge& edge);

#include "detail/edge.hpp"

#endif  // LAB04_MATH3D_EDGE_HPP_
