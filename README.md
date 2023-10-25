# Malloc - My Unique Take on the Classic C Allocator
![mybadge](https://badgen.net/badge/SKILLS/%20C,%20CUSTOM%20ALLOCATOR%20/red?scale=1.2)

#### This project is about implementing a dynamic memory allocation mechanism.


🔧 System Requirements:
   - Operating System: Linux 64_X86 Distribution / MacOS
   - Software: [make](https://www.gnu.org/software/make/), [gcc](https://gcc.gnu.org/), 

<br>

## Usage
 
To run the command, open your terminal and follow these steps:

  - To create the dynamic Librairie ```libft_malloc.so```:
  
      ```shell
      (cd /path/to/project/directory && make)
      ```

   - To run Units Tests with my malloc allocator:

      ```shell
      (cd /path/to/project/directory && make run)
      ```

   - To run same Units Tests with the original malloc:

      ```shell
      (cd /path/to/project/directory && make run_libc)
      ```

<br>

## About


This custom C implementation of the malloc library functions is functional but
not really optimized. This serves primarily as a proof of concept. Let's take a
look at the implementation in the `src` file. It creates the shared library
`libft_malloc.so` which can be used to replace malloc in all system commands.

To use my implementation on your program:

```shell
(export LD_LIBRARY_PATH=/path/to/project/directory && export LD_PRELOAD=libft_malloc.so && <program> )
```

It exposes the following methods:

```c
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t count, size_t size);
void show_alloc_mem(void); // Print informations about allocated zones
```

