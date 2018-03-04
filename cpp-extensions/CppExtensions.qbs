import qbs
import Validators

Product {
    Depends { name: 'cpp' }
    cpp.cxxLanguageVersion: 'c++11'
    cpp.includePaths: cppextModule.includePaths
    cpp.defines: cppextModule.defines

    files: [
        '**/*.h', '**/*.c',
        '**/*.hpp', '**/*.cpp',
    ]

    Export {
        id: cppextModule
        version: '0.1.2'

        property string signals
        property string namespace

        property pathList includePaths: [ '../' ]
        property stringList defines: {
            var defs = [];
            switch (signals) {
            case 'sigc': defs.push('SIGNALS=SIGNALS_SIGC'); break;
            case 'qt': defs.push('SIGNALS=SIGNALS_QT'); break;
            case 'no': defs.push('SIGNALS=NO_SIGNALS'); break;
            }
            if (typeof namespace !== 'undefined') {
                if (namespace !== '') {
                    defs.push('ANION155s_CPP_EXTENSIONS_NAMESPACE=' + namespace);
                } else {
                    defs.push('ANION155s_CPP_EXTENSIONS_NO_NAMESPACE');
                }
            }
            return defs;
        }

        Depends { name: 'sigc'; condition: signals == 'sigc' }
        Depends { name: 'Qt.core'; condition: signals == 'qt' }

        Depends { name: 'cpp' }
        cpp.includePaths: includePaths
        cpp.defines: defines

        validate: {
            var validator = new Validators.PropertyValidator('anion155-cpp-extensions');
            validator.addRegexpValidator(
                        'namespace', namespace,
                        /^([a-zA-Z_]([a-zA-Z0-9_]*::)?[a-zA-Z0-9_]*|)$/,
                        'Namespace must be valid identifier or identifiers separated by \'::\'');
            validator.setRequiredProperty('signals', signals);
            validator.addEnumValidator('signals', signals, ['sigc', 'qt']);
            validator.validate()
        }
    }
}
