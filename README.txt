JIAXIANG HU (jh3648)

Part 1
(a)OSC book
3.9 - For context switch, the kernel first saves the context of the old process
in its PCB, and then loads the saved context of the new process.

3.11 - When a process terminates, its resources are deallocated by the OS.
However, its entry in the process table has to remain until its parent process
calls wait(). For the case where the parent process terminates without calling
wait(), the init process will become the new parent to those zombie processes(whose
parents do not call wait() and exit). In this case, init process can call wait()
so that the zombie processes can be released from the process table.

(b) LKD book
1. typeof is a GNU C extension rather than standard C stuff,
    which refers tho the type of an expression.

2. offsetof is a macro in ANSI C library.
For offestof(type, member),it returns the offset of the field `member` from the
start of the structure `type`.

3. container_of(ptr, type, member)
In this macro, the structure of type `type` has a field `member`. And given
the pointer `ptr` to the filed `member`, the macro returns the address (pointer)
of the parent structure.

4.  i) typeof is an extension.
    ii) statement expression is an extension. `({})`

5. It is somehow not necessary because we can simply use `ptr` in place of
 `__mptr`. However, the purpose of the first line is do the type check so that
 it ensures the `type` has `member`. Also, if `ptr` is not the correct type,
 there will be warning message.

 Part 2
 As the requriemnt from the book, my code creats 5 birthday structure, and
 then iterates them and output the information.

 Part 3
 Redo `Part 2` without using inherent macros from `list.h`.

 Part 4
