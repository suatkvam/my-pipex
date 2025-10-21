# Pipex

**Goal:**  
This project focuses on handling **Unix pipes (`|`)** and connecting multiple shell commands together.

## Description

Your program must take **4 arguments**:

```
./pipex file1 cmd1 cmd2 file2
```

- `file1` → input file  
- `file2` → output file  
- `cmd1`, `cmd2` → shell commands with their parameters  

The program should behave **exactly like** the following shell command:

```
< file1 cmd1 | cmd2 > file2
```

## Examples

```
./pipex infile "ls -l" "wc -l" outfile
```
Equivalent to:
```
< infile ls -l | wc -l > outfile
```

```
./pipex infile "grep a1" "wc -w" outfile
```
Equivalent to:
```
< infile grep a1 | wc -w > outfile
```

## Requirements

- You must submit a **Makefile** that compiles your source files.  
  - It must not perform unnecessary relinking.  
- Your program must **never terminate unexpectedly** (e.g., segmentation fault, bus error, double free, etc.).  
- Your program must **not have memory leaks**.  
- If you are unsure, handle errors the same way as the shell command:
  ```
  < file1 cmd1 | cmd2 > file2
  ```

## Bonus Part

### Multiple Pipes

Your program should handle multiple pipes:

```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

Which should behave like:

```
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

### Here Document Support

When the first argument is `"here_doc"`, your program must support `<<` and `>>` redirections.

```
./pipex here_doc LIMITER cmd cmd1 file
```

Which should behave like:

```
cmd << LIMITER | cmd1 >> file
```
