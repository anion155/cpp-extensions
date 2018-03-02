import qbs
import Validators

Product {
    files: [
        '**/*.h', '**/*.c',
        '**/*.hpp', '**/*.cpp',
    ]

    Export {
        id: cppextModule
        version: '0.1.1'

        Depends { name: 'cpp' }
        cpp.includePaths: [ '../' ]

        property string signals
        property string namespace

        Depends { name: 'sigc'; condition: signals == 'sigc' }
        Depends { name: 'Qt.core'; condition: signals == 'qt' }
        cpp.defines: {
            var defs = [];
            switch (signals) {
            case 'sigc': defs.push('SIGNALS=SIGNALS_SIGC'); break;
            case 'qt': defs.push('SIGNALS=SIGNALS_QT'); break;
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
