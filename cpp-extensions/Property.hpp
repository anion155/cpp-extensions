#pragma once

#include <utility>
#include <cpp-extensions/extensions.hpp>

# include <sigc++/sigc++.h>

namespace cppext {

template <typename T>
class Property {
  using field_type = T;
  field_type m_field;

public:
  Property(const Property &) =delete;
  Property &operator=(const Property&) =delete;

  Property() { }
  Property(field_type &&value) : m_field(std::move(value)) { }

  Property &operator =(const field_type &value) { return set(value); }
  Property &operator =(field_type &&value) { return set(std::forward<field_type>(value)); }

  const field_type &get() const { return m_field; }
  Property &set(const field_type &value) {
    m_field = value;
    s_changed(m_field);
    return *this;
  }
  Property &set(field_type &&value) {
    m_field = std::forward<field_type>(value);
    s_changed(m_field);
    return *this;
  }

  operator field_type() { return get(); }
  operator const field_type() const { return get(); }

  template <typename C>
  explicit operator C() { return static_cast<C>(get()); }

  Property &operator +=(const field_type &value) { return set(get() + value); }
  Property &operator -=(const field_type &value) { return set(get() - value); }
  Property &operator *=(const field_type &value) { return set(get() * value); }
  Property &operator /=(const field_type &value) { return set(get() / value); }
  Property &operator %=(const field_type &value) { return set(get() % value); }
  Property &operator ^=(const field_type &value) { return set(get() ^ value); }
  Property &operator &=(const field_type &value) { return set(get() & value); }
  Property &operator |=(const field_type &value) { return set(get() | value); }
  Property &operator >>=(const field_type &value) { return set(get() >> value); }
  Property &operator <<=(const field_type &value) { return set(get() << value); }

  Property &operator ++() { return set(++m_field); }
  field_type operator ++(int) { field_type buf = get(); set(++m_field); return buf; }
  Property &operator --() { return set(--m_field); }
  field_type operator --(int) { field_type buf = get(); set(--m_field); return buf; }

  field_type operator ->() { return get(); }

public:
  using onchanged_t = sigc::signal<void, field_type>;
  using onchanged_slot = typename onchanged_t::slot_type;
  using onchanged_iterator = typename onchanged_t::iterator;

private:
  onchanged_t s_changed;

public:
  onchanged_t &signal_changed() { return s_changed; }
  onchanged_iterator onchanged(onchanged_slot &&slot) {
    return s_changed.connect(std::forward<onchanged_slot>(slot));
  }
};
}
