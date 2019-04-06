
This module adds the Caffe2 to tp_pipeline. To use this you will need to build and install the Caffe2.

## Building Caffe2 Fedora

### Dependencies
```
dnf -y update

dnf -y install \
	glog-devel \
	gtest-devel \
	leveldb-devel \
	lmdb-devel \
	opencv-devel \
	openmpi-devel \
	snappy-devel \
	protobuf-devel \
	protobuf-compiler \
	gflags-devel \
	python3-devel \
	python3-future \
	python3-numpy \
	python3-protobuf \
	python3-hypothesis \
	python3-mypy

```

### Install CUDA
```
...
```

### Build
Following instructions on:
* https://caffe2.ai/docs/getting-started.html?platform=ubuntu&configuration=compile
* https://github.com/leonardvandriel/caffe2_cpp_tutorial

```
mkdir caffe2
cd caffe2/

mkdir usr
mkdir usr/lib/

git clone https://github.com/pytorch/pytorch.git && cd pytorch
git submodule update --init --recursive
python3 setup.py build

cp torch/lib/*.so ../usr/lib/
cp torch/lib/*.a ../usr/lib/
cp -r torch/lib/include/ ../usr/

```
## Building Caffe2 iOS
```
brew install automake libtool

mkdir caffe2
cd caffe2

git clone --recursive https://github.com/pytorch/pytorch.git
cd pytorch/
git submodule update --init
./scripts/build_ios.sh

```
