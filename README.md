C++ extensions by anion155
==========

Contains Qbs Module in Product.

## Usage

In Project item add to references `cpp-extensions/cppExtensions.qbs`

    Project {
      references: [
        'cpp-extensions/cppExtensions.qbs'
      ]
    }

## `cppExtensions` module

| Property | Type   | Since | Default          | Description                |
| -------- | ------ | ----- | ---------------- | -------------------------- |
| signals     | string | 0.1.1 | undefined           | Signals api used, must be 'sigc' or 'qt'.   |
| namespace      | string | 0.1.1 | undefined            | Namespace used by library.    |

## `Validators.js` import

Extends `ModUtils.PropertyValidator` with `Regexp` and `Enum` validators.

    import 'cpp-extensions/Validators.js' as Validators

    Module {
      ...
      validate: {
        var validator = new Validators.PropertyValidator('module');
        validator.addRegexpValidator('namespace', namespace, /^[a-zA-Z_][a-zA-Z0-9_]*$/, 'Namespace must be valid identifier');
        validator.addEnumValidator('signals', signals, ['sigc', 'qt']);
        validator.validate()
      }
    }
