#! /bin/sh

qemu-aarch64 -cpu max,pauth=on -L /usr/aarch64-linux-gnu ./pac-prot.elf
