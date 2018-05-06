
require 'build';
require 'build.cc';
require 'build.visual_studio';
require 'build.xcode';
require 'build.macos';
require 'build.windows';

platform = platform or build:operating_system();
variant = variant or 'debug';
version = version or ('%s %s %s'):format(os.date('%Y.%m.%d %H:%M:%S'), platform, variant );
goal = goal or "";
jobs = jobs or 4;

build:initialize {
    variants = { 'debug', 'release', 'shipping' };
    bin = build:root( ('%s/bin'):format(variant) );
    lib = build:root( ('%s/lib'):format(variant) );
    obj = build:root( ('%s/obj'):format(variant) );
    include_directories = {
        build:root( 'src' );
        build:root( 'src/lua/src' );
        build:root( 'src/unittest-cpp' );
    };
    library_directories = {
        build:root( ('%s/lib'):format(variant) );
    };
    visual_studio = {
        sln = build:root( 'math.sln' );
    };
    xcode = {
        xcodeproj = build:root( 'math.xcodeproj' );
    };
};

build:default_targets {
    'src/math',
    'src/math/math_lua',
    'src/math/math_test'
};

buildfile 'src/lua/lua.build';
buildfile 'src/math/math.build';
buildfile 'src/unittest-cpp/unittest-cpp.build';
