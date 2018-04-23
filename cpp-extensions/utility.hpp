#pragma once

#include "_defines.hpp"
#include <sstream>
#include <utility>

CE_NAMESPACE_BEGIN

template <typename ...Args>
void UNUSED(Args&& ...args) {
    (void)(sizeof...(args));
}

class ss {
  std::stringstream m_stream;
public:
  ss(bool boolalpha = true) {
    if (boolalpha) {
      m_stream << std::boolalpha;
    }
  }

  operator std::string() {
    return m_stream.str();
  }

  template<typename T>
  ss &operator<<(const T &op) {
    m_stream << op;
    return *this;
  }
};
CE_NAMESPACE_END
