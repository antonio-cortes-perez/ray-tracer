# ray-tracer

cmake -G Ninja -S . -B build \
  -DCMAKE_C_COMPILER=clang-14 \
  -DCMAKE_CXX_COMPILER=clang++-14 \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cd build

cmake --build .

ctest --output-on-failure
