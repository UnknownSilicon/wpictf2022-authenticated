# wpictf2022-authenticated
A binary exploitation challenge using pointer authentication.


"A small section of The Archive is still using an old authenticator program from the year 2017. Find the vulnerability and gain administrator access to the system"



Example flow:

- Some setup function is called that that basically meant just to put an address on the stack
- Looping menu
- One option does alloca to allocate more space on the stack
  - Does this cause other elements already on the stack get confused? Does it move them?
- Another option signs a pointer that's supposed to be the return address, but since it's based on `sp`, it gets shifted with alloca
  - This allows the user to sign arbitrary pointers
  - This needs to be made so that the stack pointer when signing is the same as it would be when using and verifying it
- Something can be used to change control flow and use this modified return address, which should verify successfully



- Called functions will have a shifted stack pointer
- Alloca in parent function, child function would sign return address and since the sp is the same as another function, those addresses are interchangable
- Single write in a specific range?
- Alloca can also be used to overread a buffer or something and leak the stack pointer




- Print flag function. Calls isAuthenticated, then prints flag.
- If we trick the program into signing a pointer for the return address of isAuthenticated (in print flag), then we can get it to print the flag
```
print_flag:
 int is_auth = 0
 check is_auth(&is_auth)

 if(is_auth)
   print flag

return
```

- After signing the pointer, trick a vulnerable function to use it as its return address
  - Since this return address is signed with a valid key and context, it will be validated
  - Returns to the print flag function


General path:
- Use alloca to align stack pointer in a specific way
- Force signing of pointer, creating a pointer with the same context as another function
- Leak the pointer (undecided how to do this)
- Overflow a buffer in a function with the same context and write the newly signed pointer to the return address
- Jump to print flag function

General ideas:
- Stack frame manipulation
- Pointer authentication