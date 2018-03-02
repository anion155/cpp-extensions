#include "TestProperty.hpp"
#include <QTest>
#include <QSignalSpy>
#include <type_traits>

#ifdef __GNUG__
#  include <cstdlib>
#  include <memory>
#  include <cxxabi.h>
  std::string demangle(const char* name) {
    int status = -4; // some arbitrary value to eliminate the compiler warning
    std::unique_ptr<char, void(*)(void*)> res {
      abi::__cxa_demangle(name, nullptr, nullptr, &status),
      std::free
    };
    return (status==0) ? res.get() : name ;
  }
#else
  std::string demangle(const char* name) {
    return name;
  }
#endif

class SigcSignalSpy : public QList<QVariantList>, public sigc::trackable {
public:
  SigcSignalSpy() { }

  template <typename Rt, typename ...As>
  Q_SLOT Rt call(As...args) {
    this->append(QVariantList{args...});
  }
};

void TestProperty::compileTimeCheck() {
  // obj.qstring = obj.qstring_blah; // Must be NOT ALLOWED
  static_assert (!std::is_copy_constructible<cppext::Property<QString>>::value, "Properties must not be constructed as copies");
  static_assert (!std::is_copy_assignable<cppext::Property<QString>>::value, "Properties must not be assigned as copies");
}

void TestProperty::intChanged() {
  TestProperty::Object obj;
  SigcSignalSpy integer_spy;
  obj.integer.onchanged(sigc::mem_fun(&integer_spy, &SigcSignalSpy::call<void, int>));

  obj.integer = 2;
  obj.integer = int(8);
  int g = 'g';
  obj.integer = g;
  obj.integer = 'a';

  obj.integer = 5;
  obj.integer += 5;
  obj.integer -= 5;
  obj.integer *= 5;
  obj.integer /= 5;
  obj.integer %= 3;
  obj.integer ^= 5;
  obj.integer &= 12;
  obj.integer |= 5;
  obj.integer >>= 1;
  obj.integer <<= 1;

  QCOMPARE((++obj.integer).get(), 5);
  QCOMPARE((obj.integer++), 5);
  QCOMPARE((--obj.integer).get(), 5);
  QCOMPARE((obj.integer--), 5);

  QCOMPARE(integer_spy.count(), 19);
  auto it = integer_spy.begin();
  QVERIFY((*(it++))[0].toInt() == 2);
  QVERIFY((*(it++))[0].toInt() == 8);
  QVERIFY((*(it++))[0].toInt() == static_cast<int>('g'));
  QVERIFY((*(it++))[0].toInt() == static_cast<int>('a'));

  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 10);
  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 25);
  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 2);
  QVERIFY((*(it++))[0].toInt() == 7);
  QVERIFY((*(it++))[0].toInt() == 4);
  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 2);
  QVERIFY((*(it++))[0].toInt() == 4);

  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 6);
  QVERIFY((*(it++))[0].toInt() == 5);
  QVERIFY((*(it++))[0].toInt() == 4);
}

void TestProperty::strChanged() {
  TestProperty::Object obj;
  SigcSignalSpy str_spy;
  obj.qstring.onchanged(sigc::mem_fun(&str_spy, &SigcSignalSpy::call<void, QString>));
  ; // Qt creator doesn't highlight error

  obj.qstring = "blah1";
  obj.qstring = QString("blah2");
  obj.qstring = obj.qstring_blah.get();
  obj.qstring += "voohoo";

  QCOMPARE(str_spy.count(), 4);
  auto it = str_spy.begin();
  QVERIFY((*(it++))[0].toString() == "blah1");
  QVERIFY((*(it++))[0].toString() == "blah2");
  QVERIFY((*(it++))[0].toString() == "blah");
  QVERIFY((*(it++))[0].toString() == "blahvoohoo");
}

void TestProperty::intOperators() {
  TestProperty::Object obj;

  QFETCH(int, init_value);
  QFETCH(int, int_oper);
  QFETCH(bool, bool_oper);

  obj.integer = init_value;
  QCOMPARE((obj.integer+int_oper), (init_value+int_oper));
  QCOMPARE((obj.integer-int_oper), (init_value-int_oper));
  QCOMPARE((obj.integer*int_oper), (init_value*int_oper));
  if (int_oper != 0) {
    QCOMPARE((obj.integer/int_oper), (init_value/int_oper));
    QCOMPARE((obj.integer%int_oper), (init_value%int_oper));
  }
  QCOMPARE((obj.integer<<int_oper), (init_value<<int_oper));
  QCOMPARE((obj.integer>>int_oper), (init_value>>int_oper));

  QCOMPARE((obj.integer^int_oper), (init_value^int_oper));
  QCOMPARE((obj.integer&int_oper), (init_value&int_oper));
  QCOMPARE((obj.integer|int_oper), (init_value|int_oper));
  QCOMPARE((~obj.integer), (~init_value));
  QCOMPARE((!obj.integer), (!init_value));

  QCOMPARE((obj.integer<int_oper), (init_value<int_oper));
  QCOMPARE((obj.integer>int_oper), (init_value>int_oper));
  QCOMPARE((obj.integer==int_oper), (init_value==int_oper));
  QCOMPARE((obj.integer!=int_oper), (init_value!=int_oper));
  QCOMPARE((obj.integer<=int_oper), (init_value<=int_oper));
  QCOMPARE((obj.integer>=int_oper), (init_value>=int_oper));
  QCOMPARE((obj.integer&&bool_oper), (init_value&&bool_oper));
  QCOMPARE((obj.integer||bool_oper), (init_value||bool_oper));
}

void TestProperty::intOperators_data() {
  QTest::addColumn<int>("init_value");
  QTest::addColumn<int>("int_oper");
  QTest::addColumn<bool>("bool_oper");

  QTest::newRow("5 << 5") << 5 << 5 << true;
  QTest::newRow("2 << 8") << 2 << 8 << false;
  QTest::newRow("100 << 100") << 100 << 100 << true;
  QTest::newRow("0xff << 5") << 0xff << 5 << false;
  QTest::newRow("0xff << 0") << 0xff << 0 << true;
  QTest::newRow("0x0a << 5") << 0x0a << 5 << false;
  QTest::newRow("64 << 32") << 64 << 32 << true;
}
