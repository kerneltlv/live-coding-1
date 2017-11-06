#!/usr/bin/env bash
sudo apt-get install -y linux-source build-essential
echo "Extracting kernel source..."
tar xf /usr/src/linux-source-4.9.tar.xz

wget https://deb.nodesource.com/setup_8.x
chmod +x setup_8.x
sudo ./setup_8.x
sudo apt-get install -y nodejs
rm setup_8.x*

cd project
npm install