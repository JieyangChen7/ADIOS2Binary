set -x
set -e

adios_install_dir=/home/jieyang/dev/ADIOS2/install



rm -rf build
mkdir -p build
cmake -S .  -B ./build \
	    -DCMAKE_PREFIX_PATH="${adios_install_dir}"

cd build && make && cd ..
