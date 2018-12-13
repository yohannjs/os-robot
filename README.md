# Kob-E 
Source code, and wiki of the robot project of group 5 in OS, EURECOM 2018. 

Team members:

Yohann Jacob Sandvik, Embla Trasti Bygland, Kaja Gausdal and Trym Sneltvedt


# How to
If you are on your own computer and want to cross compile, simply write
```bash
./crosscompile.sh
```
And all source files will be cross compiled for the EV3 brick. Note that docker
is required for cross compilation.

The crossmake.sh file can take one argument, which it passes to the make
process inside the docker container. This means you can use crossmake.sh the
same way as you use make. For example if you want to make only the test files,
you simply write
```bash
./crosscompile.sh tests
```

If you are on Kob-E and want to compile stuff there, you'll just use the
standard `make` command. So to make just the main executeable, you write
```bash
make main
```


# Makefile
The options in our makefile are:
- `main` - make just the main executeable
- `tests` - make just the test executeables (all of them)
- `clean` - Remove all object files from the project

If you don't give make any arguments, it will make both the main executeable
and all test executeables.


## Project structure

Our project has the following structure:

- **lib** _Required libraries_
- **bin** _Compiled executeables_
- **src** _Source code_
    - **interfaces** _HW/Robot specific modules_
    - **adapters** _Higher lever modules_
    - main.c _Main source file_
- **tests** _Test source files for source code_
- crossmake.sh _Script for cross compilation with Docker_
- Makefile _Project makefile_

