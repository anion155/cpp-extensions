#pragma once

#include "_defines.hpp"
#include <utility>
#include <cpp-extensions/utility.hpp>

#if IS_SIGNALS_SIGC
# include <sigc++/sigc++.h>
#elif IS_SIGNALS_QT
# include <QObject>
#endif

CE_NAMESPACE_BEGIN

template <typename T>
class Property
#if IS_SIGNALS_QT
    : public QObject
{
  Q_OBJECT
#else
{
#endif
  using field_type = T;
  field_type m_field;

public:
  Property(const Property &) =delete;
  Property &operator=(const Property&) =delete;

  // FIXME: warn on `const Property<_Type>;`
  Property() { }
  Property(const field_type &value) : m_field(value) { }
  Property(field_type &&value) : m_field(std::move(value)) { }
  Property(Property &&p) : m_field(std::move(p.m_field)) { }

  Property &operator =(const field_type &value) { return set(value); }
  Property &operator =(field_type &&value) { return set(std::forward<field_type>(value)); }

  field_type &get() { return m_field; }
  const field_type &get() const { return m_field; }
  Property &set(const field_type &value) {
    m_field = value;
#if IS_SIGNALS_SIGC
    s_changed.emit(m_field);
#elif IS_SIGNALS_QT
    emit changed(m_field);
#endif
    return *this;
  }
  Property &set(field_type &&value) {
    m_field = std::forward<field_type>(value);
#if IS_SIGNALS_SIGC
    s_changed.emit(m_field);
#elif IS_SIGNALS_QT
    emit changed(m_field);
#endif
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

#if IS_SIGNALS_SIGC
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
#elif IS_SIGNALS_QT
public:
  void changed(field_type value) Q_SIGNAL;
#endif
};

template <typename _Type>
CE_NAMESPACE::ss &operator<<(CE_NAMESPACE::ss &that, const CE_NAMESPACE::Property<_Type> &obj) {
    that << obj.get();
    return that;
}
CE_NAMESPACE_END
