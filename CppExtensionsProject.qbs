import qbs

Project {
    qbsSearchPaths: [
        'qbs/'
    ]
    SubProject {
        filePath: 'cpp-extensions/CppExtensions.qbs'
    }
    SubProject {
        filePath: 'tests/tests.qbs'
        Properties {
            condition: false
        }
    }
}
