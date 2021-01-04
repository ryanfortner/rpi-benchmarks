#!/bin/bash
cd ~/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/vkmark/vkmark.deb
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/mesa-vulkan-drivers-rpi4.deb
sudo apt install --fix-missing -y ~/mesa-vulkan-drivers-rpi4.deb
sudo apt install --fix-missing -y ~/vkmark.deb
rm -f ~/vkmark.deb
rm -f ~/mesa-vulkan-drivers-rpi4.deb

echo "Done"
