from pwn import *
import os

os.environ["QEMU_LD_PREFIX"] = "/usr/aarch64-linux-gnu"

context.arch = "aarch64"

elf = ELF("./pac-prot.elf")

print(pwnlib.qemu.ld_prefix())

p = process("./pac-prot.elf")

p.readuntil("(5): ")



p.interactive()