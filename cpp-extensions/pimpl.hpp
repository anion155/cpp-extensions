#pragma once

#include "_defines.hpp"

#define CE_PIMPL_DECLARE_PRIVATE \
  inline Impl *impl_func() { return reinterpret_cast<Impl *>(impl_ptr); } \
  inline const Impl* impl_func() const { return reinterpret_cast<const Impl *>(impl_ptr); } \
  friend class Impl; \
  DEFINE_REQUIRE_SEMICOLON

#define CE_PIMPL_DECLARE_PUBLIC(Class) \
  inline Class* pub_func() { return static_cast<Class *>(pub_ptr); } \
  inline const Class* pub_func() const { return static_cast<const Class *>(pub_ptr); } \
  friend class Class; \
  DEFINE_REQUIRE_SEMICOLON

#define CE_IMPL \
  Impl * const i = impl_func()

#define CE_PUBL(Class) \
  Class * const q = q_func()
