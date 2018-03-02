#include <QObject>
#include <cpp-extensions/extensions.hpp>
#include <memory>

class TestProperty: public QObject {
  Q_OBJECT

  struct SubObject {
    long g = 8;
    std::string message;
    SubObject(std::string str) : message(str) { }
  };
  class Object {
  public:
    cppext::Property<int> integer = 8;
    cppext::Property<int *> pointer = new int(8);
    cppext::Property<SubObject *> object = new SubObject("voodoo");
    cppext::Property<std::shared_ptr<SubObject>> smart_object = std::make_shared<SubObject>("voodoo");
    cppext::Property<const char*> array = "array rules!";
    cppext::Property<bool> boolean = false;
    cppext::Property<std::string> string = std::string("foo");
    cppext::Property<QString> qstring = QString("foo");
    cppext::Property<QString> qstring_blah = QString("blah");
    using functor_t = std::string (*)(void);
    cppext::Property<functor_t> functor = static_cast<functor_t>([]() -> std::string { return ""; });
  };

private Q_SLOTS:
  void compileTimeCheck();
  void intChanged();
  void strChanged();
  void intOperators();
  void intOperators_data();
};
