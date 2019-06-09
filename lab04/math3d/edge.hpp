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

constexpr Edge::Edge(std::size_t p1, std::size_t p2)
    : p1_(p1), p2_(p2) {}

constexpr auto Edge::p1() -> reference {
  return p1_;
}

constexpr auto Edge::p1() const -> const_reference {
  return p1_;
}

constexpr auto Edge::p2() -> reference {
  return p2_;
}

constexpr auto Edge::p2() const -> const_reference {
  return p2_;
}

constexpr auto Edge::operator[](size_type index) -> reference {
  return *(&p1_ + index);
}

constexpr auto Edge::operator[](size_type index) const -> const_reference {
  return *(&p1_ + index);
}

inline auto Edge::at(size_type index) -> reference {
  if (index >= 2)
    throw std::out_of_range("Edge::at");
  return *(&p1_ + index);
}

inline auto Edge::at(size_type index) const -> const_reference {
  if (index >= 2)
    throw std::out_of_range("Edge::at");
  return *(&p1_ + index);
}

inline std::istream& operator>>(std::istream& is, Edge& edge) {
  is >> edge.p1() >> edge.p2();
  return is;
}

inline std::ostream& operator<<(std::ostream& os, const Edge& edge) {
  os << edge.p1() << ' ' << edge.p2();
  return os;
}

#endif  // LAB04_MATH3D_EDGE_HPP_
