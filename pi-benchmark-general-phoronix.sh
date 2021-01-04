#!/bin/bash
#
# Benchmark script for Raspberry Pi OS.
#
# WARNING: This script is meant to be run as the root user.
# This script should never be run on a system/partition you
# care about. You should only run this on a system that you
# intend to use only for benchmarking and can reinstall or
# re-flash easily.
#
# Usage: sudo ./pi-general-benchmark.sh

# Fail on error.
set -e

# Set this to "~/.phoronix-test-suite" if not running as root.
PHORONIX_CONFIG_PATH="/var/lib/phoronix-test-suite"

# Verify script is running as root.
if [ "$EUID" -ne 0 ]
  then echo "Please run this script as root (e.g. with sudo)."
  exit
fi

# Change directories into home folder.
cd ~

# Install prerequisites.
apt-get install -y php7.3-cli php7.3-xml

# Download test suite.
curl -LO https://github.com/chunky-milk/rpi-benchmarks/raw/main/phoronix-test-suite-9.6.1.tar.gz
tar -xvf phoronix-test-suite-9.6.1.tar.gz
cd phoronix-test-suite

# Accept terms and print system info.
./phoronix-test-suite system-info <<-END
y
n
n
END

# List recommended tests.
./phoronix-test-suite list-recommended-tests

# Ensure config directory exists.
mkdir -p $PHORONIX_CONFIG_PATH/test-suites/local/raspberrypi

# Copy configuration into place.
tee $PHORONIX_CONFIG_PATH/test-suites/local/raspberrypi/suite-definition.xml <<EOF
<?xml version="1.0"?>
<!--Phoronix Test Suite v9.6.1-->
<PhoronixTestSuite>
  <SuiteInformation>
    <Title>RaspberryPi</Title>
    <Version>1.0.0</Version>
    <TestType>System</TestType>
    <Description>General system tests for the Raspberry Pi.</Description>
    <Maintainer>Jeff Geerling</Maintainer>
  </SuiteInformation>
  <Execute>
    <Test>pts/encode-mp3</Test>
  </Execute>
  <Execute>
    <Test>pts/x264</Test>
  </Execute>
  <Execute>
    <Test>pts/phpbench</Test>
  </Execute>
</PhoronixTestSuite>
EOF

# Run benchmark suite.
./phoronix-test-suite benchmark raspberrypi
