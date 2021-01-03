#!/bin/bash

if [ ! `which stressberry-run` ]; then
  echo "Installing stressberry package from repositories."
  sleep 2
  sudo apt-get update
  sudo apt-get install -y stress python-pip gpicview
  pip install stressberry
fi

rm -f ~/rpi-benchmark/stressberry/out.dat
rm -f ~/rpi-benchmark/stressberry/out.png

clear
~/.local/bin/stressberry-run ~/rpi-benchmark/stressberry.out.dat
~/.local/bin/stressberry-plot -o ~/rpi-benchmark/stressberry/out.png ~/rpi-benchmark/stressberry/out.dat
gpicview ~/rpi-benchmark/stressberry/out.png

echo ""
echo "Close this window to exit."
echo ""
sleep 1h
