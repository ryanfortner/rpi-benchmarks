#!/bin/bash

if [ ! `which speedtest-cli` ]; then
  echo "Installing speedtest-cli package from repositories"
  sleep 2
  sudo apt-get update
  sudo apt-get install -y speedtest-cli
fi

/usr/bin/speedtest-cli --simple

echo ""
echo "Close this window to exit."
echo ""
sleep 1h
