#! /bin/sh

qemu-aarch64 -cpu max,pauth=on -g 8091 -L /usr/aarch64-linux-gnu ./pac.elf
