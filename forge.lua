
variant = variant or 'debug';
version = version or ('%s %s %s'):format(os.date('%Y.%m.%d %H:%M:%S'), platform, variant );

local forge = require 'forge.cc' {
    identifier = 'cc_${platform}_${architecture}';
    platform = forge:operating_system();
    bin = forge:root( ('%s/bin'):format(variant) );
    lib = forge:root( ('%s/lib'):format(variant) );
    obj = forge:root( ('%s/obj'):format(variant) );
    include_directories = {
        forge:root( '..' );
        forge:root( 'src/lua/src' );
        forge:root( 'src/unittest-cpp' );
    };
    library_directories = {
        forge:root( ('%s/lib'):format(variant) );
    };
    visual_studio = {
        sln = forge:root( 'math.sln' );
    };
    xcode = {
        xcodeproj = forge:root( 'math.xcodeproj' );
    };
};

buildfile 'math.forge';
buildfile 'src/lua/lua.forge';
buildfile 'src/unittest-cpp/unittest-cpp.forge';

forge:all {
    'math_lua/all',
    'math_test/all'
};
