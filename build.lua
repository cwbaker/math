
require 'forge';
require 'forge.cc';
require 'forge.visual_studio';
require 'forge.xcode';
require 'forge.macos';
require 'forge.windows';

platform = platform or forge:operating_system();
variant = variant or 'debug';
version = version or ('%s %s %s'):format(os.date('%Y.%m.%d %H:%M:%S'), platform, variant );
goal = goal or "";
jobs = jobs or 4;

forge:initialize {
    variants = { 'debug', 'release', 'shipping' };
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

forge:default_targets {
    'math_lua',
    'math_test'
};

buildfile 'math.build';
buildfile 'src/lua/lua.build';
buildfile 'src/unittest-cpp/unittest-cpp.build';
