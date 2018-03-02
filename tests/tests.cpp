#include <QTest>
#include <TestProperty.hpp>

int main(int argc, char *argv[]) {
    QTEST_SET_MAIN_SOURCE_PATH;
    int code = QTest::qExec(new TestProperty(), argc, argv); if (code != 0) { return code; }
    return 0;
}
