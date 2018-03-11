Create a directory build:

> mkdir build;

Go into that directory

> cd build;

You can choose to build a release version with:

> cmake ../ -DCMAKE_BUILD_TYPE=Release

or a debug version with

> cmake ../ -DCMAKE_BUILD_TYPE=Debug

And build everything with

> make
