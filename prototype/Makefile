all: pac.c
	aarch64-linux-gnu-gcc-9 -g -march=armv8.3-a -mbranch-protection=standard -no-pie -Wl,-z,norelro -Wall -fno-stack-protector -o pac-prot.elf pac.c
	aarch64-linux-gnu-gcc-9 -g -march=armv8.3-a -no-pie -Wl,-z,norelro -Wall -fno-stack-protector -o pac.elf pac.c