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

```c
print_flag:
 int is_auth = 0
 check is_auth(&is_auth)

 if(is_auth)
   print flag

 return
  // After the alloca in the main loop has been called a sufficient number of times
  // the return address of this function will have the same context as the return address of `test`.
  // This means that this return address could be replaced with that of test or the return
  // address of test could be replaced with that of this.
  // This is where it gets tricky. Basically the only reasonable way to do this is to leak an address.
  // This could be done with a contrived "enter address (within a range) to leak".
  // This could also be like, print the value of an address at a specific offset from the sp on the stack

  // In this case, the attacker should sign the return address of `is_auth`, which can be forced to be put on the stack
  // Next, after leaking the signed address, overwrite the return address of `test` with it
  // This will then jump to after is_auth. By carefully positioning the stack again before this, is_auth would be set to 1
  // causing the check to pass

test:
 // Here to force pointer auth, but should also have a vulnerability that allows overwriting the return address

 char auth[10]

 // Normally, this would cause a seg fault on return because of pointer auth,
 // but if you overwrite the return address with one that was also signed using the same sp, you can jump there instead
 gets(auth)

 return

big_stack:
 char large[2048] // Large buffer to push the stack pointer far

 test() // Force pointer auth to occur, signing 'test's' return address with this large sp as context

 return

main_loop:

 char* buf

 while true:

  sscanf() // Get some sort of input to decide what to do

  1:
   buf = alloca(64)
  2:
   print_flag() // Need to make sure people can't authenticate here
  3:
   print(buf[64]) // Something to leak the address
  4:
   test()

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