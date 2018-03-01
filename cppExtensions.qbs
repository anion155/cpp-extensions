import qbs
import 'Validators.js' as Validators

Product {
    id: cppextProduct
    // type: [linkage + 'library']
    // property string linkage: 'static'

    Depends { name: 'cpp' }
    cpp.includePaths: [ './' ]

    files: [
        '**/*.h', '**/*.c',
        '**/*.hpp', '**/*.cpp',
    ]

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

}
