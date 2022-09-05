#! /bin/sh

qemu-aarch64 -cpu max,pauth=off -L /usr/aarch64-linux-gnu ./pac.elf
