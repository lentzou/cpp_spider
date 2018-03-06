#!/bin/bash

tput setaf 3
echo "the following libraries will be install : "
echo "- cmake"
echo "- Boost"
echo "- OpenSSL"
echo "- SFML"
echo ""

sleep 3

mkdir lib_linux

tput setaf 1
echo "Downloading cmake.."
echo ""

wget -q -R . https://cmake.org/files/v3.9/cmake-3.9.4-Linux-x86_64.tar.gz

echo "Unpacking.."
echo ""

gunzip cmake-3.9.4-Linux-x86_64.tar.gz

tar -xsvf cmake-3.9.4-Linux-x86_64.tar &>/dev/null

rm -f cmake-3.9.4-Linux-x86_64.tar

mv cmake-3.9.4-Linux-x86_64 lib_linux/cmake

echo "Downloading boost.."
echo ""

wget -q -R . https://dl.bintray.com/boostorg/release/1.65.1/source/boost_1_65_1.tar.gz

echo "Unpacking.."
echo ""

gunzip boost_1_65_1.tar.gz

tar -xsvf boost_1_65_1.tar &>/dev/null

rm -f boost_1_65_1.tar

mv boost_1_65_1 lib_linux/boost

echo "Downloading openssl.."
echo ""

wget -q -R . https://www.openssl.org/source/openssl-1.1.0f.tar.gz

echo "Unpacking.."
echo ""

gunzip openssl-1.1.0f.tar.gz

tar -xsvf openssl-1.1.0f.tar &>/dev/null

rm -f openssl-1.1.0f.tar

mv openssl-1.1.0f lib_linux/openssl

echo "Downloading SFML.."
echo ""

wget -q -R . https://www.sfml-dev.org/files/SFML-2.4.2-linux-gcc-64-bit.tar.gz

echo "Unpacking.."
echo ""

gunzip SFML-2.4.2-linux-gcc-64-bit.tar.gz

tar -xsvf SFML-2.4.2-linux-gcc-64-bit.tar &>/dev/null

rm -f SFML-2.4.2-linux-gcc-64-bit.tar

mv SFML-2.4.2 lib_linux/sfml

tput setaf 3

echo "Done."
echo ""

lib_linux/cmake/bin/cmake .
