#!/bin/bash

if [ ! `which glmark2` ]; then
  echo "Installing glmark2 package from repositories"
  sleep 2
  sudo apt-get update
  wget -O ~/glmark2.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/glmark2.deb
  sudo apt install --fix-missing -y ~/glmark2.deb
  clear
fi

clear
glmark2

echo ""
echo "Close this window to exit."
echo ""
sleep 1h
