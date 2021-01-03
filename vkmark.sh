#!/bin/bash

if [ ! `which vkmark` ]; then
  echo "Downloading and installing vkmark.deb."
  sleep 2
  sudo apt-get update
  wget -O ~/drivers.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/mesa-vulkan-drivers-rpi4.deb
  wget -O ~/vkmark.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/vkmark.deb
  sudo apt install --fix-missing -y ~/vkmark.deb
  clear
fi

clear
vkmark

echo ""
echo "Close this window to exit."
echo ""
sleep 1h
