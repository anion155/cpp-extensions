#pragma once

#if defined(__clang__) || defined(__GNUC__) || defined(__GNUG__)

#if defined(__clang__)
#  define PRAGMA_COMPILLER clang
#else
#  define PRAGMA_COMPILLER GCC
#endif

#  define QUOTE(STR) #STR
#  define PRAGMA(COMMAND) \
    _Pragma(QUOTE(COMMAND))
#  define PRAGMA_DIAGNOSTIC(COMMAND) \
    PRAGMA(PRAGMA_COMPILLER diagnostic COMMAND)

#  define PRAGMA_DIAGNOSTIC_PUSH \
    PRAGMA_DIAGNOSTIC(push)
#  define PRAGMA_DIAGNOSTIC_IGNORED(WARNING) \
    PRAGMA_DIAGNOSTIC(ignored QUOTE(-W##WARNING))
#  define PRAGMA_DIAGNOSTIC_POP \
    PRAGMA_DIAGNOSTIC(pop)

#  if defined(__clang__)
#    define PRAGMA_DIAGNOSTIC_IGNORED_CPP14_EXTENSIONS \
       PRAGMA_DIAGNOSTIC_IGNORED(c++14-extensions)
#    define PRAGMA_DIAGNOSTIC_IGNORED_EXTRA_SEMI \
       PRAGMA_DIAGNOSTIC_IGNORED(extra-semi)
#  else
#    define PRAGMA_DIAGNOSTIC_IGNORED_CPP14_EXTENSIONS
#    define PRAGMA_DIAGNOSTIC_IGNORED_EXTRA_SEMI
#  endif

#  define PRAGMA_DIAGNOSTIC_IGNORED_OLD_STYLE_CAST \
     PRAGMA_DIAGNOSTIC_IGNORED(old-style-cast)
#  define PRAGMA_DIAGNOSTIC_IGNORED_ZERO_AS_NULL_POINTER_CONSTANT \
     PRAGMA_DIAGNOSTIC_IGNORED(zero-as-null-pointer-constant)

#else

#  define PRAGMA_COMPILLER
#  define QUOTE(STR) #STR
#  define PRAGMA(COMMAND)
#  define PRAGMA_DIAGNOSTIC(COMMAND)

#  define PRAGMA_DIAGNOSTIC_PUSH
#  define PRAGMA_DIAGNOSTIC_POP
#  define PRAGMA_DIAGNOSTIC_IGNORED(WARNING)

#endif

