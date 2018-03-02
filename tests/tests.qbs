import qbs

CppApplication {
    Depends { name: 'Qt.testlib' }
    Depends { name: 'CppExtensions' }
    CppExtensions.signals: 'sigc'

    Depends { name: 'cpp' }
    cpp.includePaths: [ '.' ]
    cpp.defines: [ 'QT_NO_KEYWORDS' ]

    files: [
        '**/Test*.h', '**/Test*.c',
        '**/Test*.hpp', '**/Test*.cpp',
    ]
}
