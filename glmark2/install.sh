#!/bin/bash
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/glmark2/glmark2.deb
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/mesa-vulkan-drivers-rpi4.deb
sudo apt install --fix-missing -y ~/mesa-vulkan-drivers-rpi4.deb
sudo apt install --fix-missing -y ~/glmark2.deb

echo "Done"
