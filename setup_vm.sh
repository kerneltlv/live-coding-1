#!/usr/bin/env bash
wget https://deb.nodesource.com/setup_8.x
chmod +x setup_8.x
sudo ./setup_8.x
sudo apt-get install -y nodejs
sudo apt-get install -y build-essential
cd /project
npm install