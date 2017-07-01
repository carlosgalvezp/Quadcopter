#!/bin/bash
set -e

# Reference:
# https://docs.docker.com/engine/installation/linux/docker-ce/ubuntu/#install-from-a-package

# Uninstall older versions of docker
sudo apt-get remove --assume-yes docker docker-engine docker.io

# Setup the Docker repository
sudo apt-get update
sudo apt-get install --assume-yes \
    apt-transport-https \
    ca-certificates \
    curl \
    software-properties-common

curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
sudo apt-key fingerprint 0EBFCD88
sudo add-apt-repository \
   "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
   $(lsb_release -cs) \
   stable"

# Install Docker CE
sudo apt-get update
sudo apt-get install --asume-yes docker-ce

# Test that docker was successfully installed
sudo docker run hello-world

# Create docker group
if [ $(getent group docker) ]; then
    echo "The docker group already exists"
else
    sudo groupadd docker
fi

# Add user to group
if id -nG "$USER" | grep -qw docker; then
    echo "The user $USER is already member of the docker group"
else
    sudo usermod -aG docker $USER
    echo "To finish the setup, please log out and back in"
fi

echo "Finished installing docker!"
