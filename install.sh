#!/bin/bash

DIRECTORY="$(dirname "$(dirname "$( cd "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )")")"

function error {
  echo -e "\\e[91m$1\\e[39m"
  exit 1
}

"${DIRECTORY}/pkg-install" "stress lxterminal gpicview python-pip unzip yad hdparm sysbench speedtest-cli" "$(dirname "$0")" || exit 1

mkdir ~/rpi-benchmark | error "failed to create directory!"
mkdir ~/rpi-benchmark/linpack

echo "Installing Stressberry"
sleep 2
pip install stressberry | error "Failed to install stressberry!"

echo "Installing Linpack benchmarks to install directory"
wget -O ~/rpi-benchmark/linpack/linpack-arm.zip https://github.com/chunky-milk/rpi-benchmarks/raw/main/Linpack-Benchmarks.zip | error "Failed to download Linpack ARM benchmarks!"
unzip ~/rpi-benchmark/linpack/linpack-arm.zip | error "Failed to unzip file!"
rm ~/linpack-arm.zip

echo "Installing glmark2 and vkmark (Vulkan and OpenGL benchmarks)"
wget -O ~/drivers.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/mesa-vulkan-drivers-rpi4.deb | error "Failed to download drivers!"
sudo apt install --fix-missing -y ~/drivers.deb | error "Failed to install mesa & vulkan drivers!"
wget -O ~/glmark2.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/glmark2.deb | error "Failed to download glmark2!"
sudo apt install --fix-missing -y ~/glmark2.deb | error "Failed to install glmark2!"
wget -O ~/vkmark.deb https://github.com/chunky-milk/rpi-benchmarks/raw/main/vkmark.deb | error "Failed to download vkmark!"
sudo apt install --fix-missing -y ~/vkmark.deb

echo "Cleaning up"
cd ~/
rm -f drivers.deb
rm -f glmark2.deb
rm -f vkmark.deb

cd ~/rpi-benchmark/
mkdir stressberry 
mkdir all
mkdir vkmark
mkdir glmark2
mkdir gui
mkdir icon
mkdir internet-speedtest
cd stressberry
touch out.dat
touch out.png
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/stressberry.sh && chmod +x stressberry.sh

cd ~/rpi-benchmark/gui/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/gui.sh
chmod +x gui.sh

cd ~/rpi-benchmark/all/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/all.sh
chmod +x all.sh

cd ~/rpi-benchmark/vkmark/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/vkmark.sh
chmod +x vkmark.sh

cd ~/rpi-benchmark/internet-speedtest/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/internet-speedtest.sh
chmod +x internet-speedtest.sh

cd ~/rpi-benchmark/glmark2/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/glmark2.sh
chmod +x glmark2.sh

cd ~/rpi-benchmark/icon/
wget https://github.com/chunky-milk/rpi-benchmarks/raw/main/icon.png
cd ~/

echo "Creating desktop shortcuts"

echo "[Desktop Entry]
Name=Raspberry Pi Benchmarks
Comment=Suite of Raspberry Pi benchmarks
Exec='$HOME/rpi-benchmark/gui/gui.sh'
Icon='$HOME/rpi-benchmark/icon/icon'
Terminal=false
StartupNotify=true
Type=Application
Categories=Utility;" > ~/.local/share/applications/rpi-benchmark.desktop || error "Failed to create menu button!"
