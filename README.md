# OpenRoadEd on Linux

OpenRoadEd is simple application designed to create both logical (OpenDRIVE standard) and geometrical (OpenSceneGraph) descriptions of road networks created by Dmitri and Egor Kurteanu. 

This fork was adapted to compile on modern Linux operating systems by Hermann Höhne and Hamid Ebadi.

![OpenRoadEdLinux](Screenshots/OpenRoadEdLinuxXodr.png)

## Build Instructions 

### Ubuntu 20.04

#### Install dependencies

```
sudo apt install git cmake g++ libopenscenegraph-dev qt5-default
```

#### Build osgQt

This can be skipped if libopenscenegraph-dev installed osgQt/GraphicsWindowQt header file in /usr/local/include/osgQt/GraphicsWindowQt (Ubuntu 18.04)

```
cd ~
git clone https://github.com/openscenegraph/osgQt.git
cd osgQt/
git checkout 6e4de
mkdir build
cd build
cmake ..
make
sudo make install
```

#### Build OpenRoadEd

```
cd ~
git clone https://github.com/fhwedel-hoe/OpenRoadEd.git
mkdir OpenRoadEd/OpenRoadEd/build
cd OpenRoadEd/OpenRoadEd/build
cmake ..
make
```

### Windows 10

#### Install dependencies

Download and build dependencies (this may take hours).

    …\vcpkg\vcpkg.exe install osg:x64-windows osgQt:x64-windows qt5:x64-windows

Static builds will not work.

#### Build OpenRoadEd

    cd OpenRoadEd\OpenRoadEd\build
    …\VisualStudio\2019\Community\VC\Auxiliary\Build\vcvars64.bat
    cmake .. -GNinja -DVCPKG_TARGET_TRIPLET=x64-windows -DCMAKE_TOOLCHAIN_FILE=…\vcpkg\scripts\buildsystems\vcpkg.cmake
    cmake --build .

## Run OpenRoadEd

Execute OpenRoadEd binary from the same directory as "Resources" dicrectory by running the following commands:

```
cd ~/OpenRoadEd/
LC_ALL=C ./OpenRoadEd/build/OpenRoadEd
```

Forcing the locale is a necessary workaround for issue #8.

Please read the [OpenDrive Road Editor Usage Guide](Help/OpenRoadEdHelp.pdf) document for software instruction.


## Origin

OpenRoadEd was created as part of this [master's thesis by Dmitri and Egor Kurteanu](http://hdl.handle.net/2077/23047) that is accessible from [sourceforge](https://sourceforge.net/projects/openroaded/) and [gitlab](https://gitlab.com/OpenRoadEd/OpenRoadEd).
