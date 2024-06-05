OpenUSM
======

OpenUSM is an open-source game engine that supports playing Ultimate Spider-Man by Treyarch. You need to own the game for OpenUSM to play Ultimate Spider-Man.

Current Status
--------------

The engine is not complete and is at the prototyping stage.

Requiments:
* Linux or Ubuntu on Windows 10
* MinGW-w64 compiler


How to build and install:
------------------------
* Copy `shaders` directory from project to the game's folder.
* Rename `binkw32.dll` in the game's folder to `binkw32_.dll`
* Download the repository to a directory convenient for you using the command:  
`git clone --recursive https://gitlab.com/MrMartinIden/openusm.git`  
    or  
`git clone https://gitlab.com/MrMartinIden/openusm.git && cd openusm && git submodule update --init --recursive`

* `cd openusm`
* `cmake -B build` (a `build` directory and makefile will be created)
* `cd build`
* `make -jN`, where N - how many threads you want to allot for compiling.
* Copy the compiled `binkw32.dll` from `build` directory to the game's folder.


License
------------

The code should only be used for educational, documentation and modding purposes.
I do not encourage piracy or commercial use.
Please keep derivate work open source and give proper credit.
