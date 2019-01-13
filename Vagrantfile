# This file is part of termpong.
#
# Copyright (c) 2019 Andrew Steel <copyright@andrewsteel.net>
#
# SPDX-License-Identifier: GPL-3.0-only
#
# The GNU General Public License Version 3 only:
#
# This is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License Version 3
# as published by the Free Software Foundation.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file. If not, see <https://www.gnu.org/licenses/>.

Vagrant.configure("2") do |config|
	config.vm.box = "generic/debian9"
	config.vm.hostname = "vm-termpong"
	config.vm.post_up_message = $post_up_message
	config.vm.provision "shell",
		inline: $provision_shell_inline_always,
		run: "always"
	config.vm.synced_folder ".", "/shared"
end

$post_up_message = <<-'EOF'
	Machine is ready, run `vagrant ssh` to enter.
	Shared directory is available at `~/termpong`.
	EOF

$provision_shell_inline_always = <<-'EOF'
	#!/bin/sh
	# Create shared directory in "${HOME}/termpong".
	sudo -u 'vagrant' sh -c '
		rm -f "${HOME}/termpong"
		ln -s "/shared" "${HOME}/termpong"
	'
	EOF
