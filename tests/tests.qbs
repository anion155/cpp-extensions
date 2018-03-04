import qbs

CppApplication {
    builtByDefault: false

    Depends { name: 'Qt.testlib' }
    Depends { name: 'CppExtensions' }
    CppExtensions.signals: 'sigc'

    Depends { name: 'cpp' }
    cpp.includePaths: original.concat([ './' ])
    cpp.defines: original.concat([ 'QT_NO_KEYWORDS' ])

    files: [
        '**/*.h', '**/*.c',
        '**/*.hpp', '**/*.cpp',
    ]
}
