var ModUtils = require('qbs.ModUtils');

var PropertyValidator = (function (superClass) {
  function PropertyValidator(modulename) {
    PropertyValidator.__super__.constructor.call(this, modulename);
  }

  var extend = function (child, parent) {
    for (var key in parent) {
      if (hasProp.call(parent, key)) child[key] = parent[key];
    }

    function ctor() {
      this.constructor = child;
    }
    ctor.prototype = parent.prototype;
    child.prototype = new ctor(); // @disable-check M307
    child.__super__ = parent.prototype;
    return child;
  };
  var hasProp = {}.hasOwnProperty;
  extend(PropertyValidator, superClass);

  PropertyValidator.prototype.addRegexpValidator = function (propertyName, propertyValue, regexp, msg) {
    this.addCustomValidator(
      propertyName, propertyValue,
      function (value) {
        return regexp.test(value);
      }, msg
    );
  }
  PropertyValidator.prototype.addEnumValidator = function (propertyName, propertyValue, allowedValues) {
    this.addCustomValidator(
      propertyName, propertyValue,
      function (value) {
        return allowedValues.indexOf(value) >= 0;
      }, 'Property value must be one of this ' + JSON.stringify(allowedValues)
    );
  }

  return PropertyValidator;
})(ModUtils.PropertyValidator);