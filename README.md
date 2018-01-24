# See
Idea of this project is to learn modern C (C11),
 and at the same time create something potentially useful, so I chose 
 rfc2161 as target to implement workable, self-contained (inventing bicycles
 along the way!) web server.

Also I'll try to write proper tests, and do all other modern *useful* software
 practices.


## Building
This project uses [musl-gcc](https://www.musl-libc.org/), based on personal
 perference. I'll try to avoid any wizardry that would prevent this project to
 build on [glibc](https://www.gnu.org/software/libc/).

To build project, create and enter `build` directory and run command 
 `cmake .. -GNinja` (I use Ninja build tool). After that, `ninja` command run
 in the same directory will compile all changed files.
