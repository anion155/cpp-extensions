import qbs

Project {
    qbsSearchPaths: [
        'qbs/'
    ]
    references: [
        'cpp-extensions/CppExtensions.qbs',
        'tests/tests.qbs',
    ]
}
