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
  return is >> edge.p1() >> edge.p2();
}

inline std::ostream& operator<<(std::ostream& os, const Edge& edge) {
  return os << edge.p1() << ' ' << edge.p2();
}
