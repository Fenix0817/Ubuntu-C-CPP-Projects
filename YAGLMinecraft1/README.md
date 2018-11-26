# YAGLMinecraft1


Remember!
This is compiled with flags that prevent
optimization by the compiler.  These should
be removed for anyone not intending to debug
the code with the generated assembly.
Instructions for reading the assembly code:
Add the flags '-g -O0' 
Run 'objdump -dS the_name_of_the_binary > name_of_the_generated_dump'
To view the dump file, run 'vi name_of_the_generated_dump'. 
