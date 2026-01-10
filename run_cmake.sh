
#delete old build path if exists
rm -rf build

# build the tool
cmake -B build -S . -DCMAKE_PREFIX_PATH=/usr/lib/qt6

# create build components and compile
cmake --build build


# start the keyboard tool.
sudo ./build/keyboard
