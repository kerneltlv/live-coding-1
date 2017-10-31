# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
	config.vm.box = "debian/stretch64"
	config.vm.synced_folder ".", "/project"

	config.vm.provision "shell", path: "setup_vm.sh"
end
