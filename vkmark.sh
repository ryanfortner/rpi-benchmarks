#!/bin/bash

if [ ! `which vkmark` ]; then
  echo "Downloading and installing vkmark.deb."
  sleep 2
  sudo apt-get update
  wget -O ~/drivers.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/mesa-vulkan-drivers-rpi4.deb | error "Failed to download drivers!"
  sudo apt install --fix-missing -y ~/drivers.deb | error "Failed to install mesa & vulkan drivers!"
  wget -O ~/vkmark.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/vkmark.deb | error "Failed to download vkmark!"
  sudo apt install --fix-missing -y ~/vkmark.deb
fi

clear
vkmark

echo ""
echo "Close this window to exit."
echo ""
sleep 1h
