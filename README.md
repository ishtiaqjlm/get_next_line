*This project has been created as part of the 42 curriculum by ishtiahm.*

# get_next_line

## Description

`get_next_line` is a 42 project that implements a function capable of reading a file descriptor one line at a time.

The main function is:

```c
char	*get_next_line(int fd);
```

Each call to `get_next_line()` returns the next line from the file descriptor. The returned line includes the newline character (`\n`) when one is present. If the final line does not end with a newline, it is returned without one.

The project is designed to work with different `BUFFER_SIZE` values and with repeated calls to the function until the end of the file is reached.

The implementation uses a static stash to preserve unread data between calls.

## Features

* Reads one line per `get_next_line()` call.
* Works with different `BUFFER_SIZE` values.
* Handles lines with and without a final newline.
* Handles empty lines.
* Handles empty files.
* Preserves unread data between function calls.
* Dynamically grows the internal stash when more space is required.
* Avoids repeatedly copying the complete stash when new data is read.
* Uses only the functions permitted by the project subject.

## Algorithm

The implementation uses a **dynamic stash** to store data that has been read but has not yet been returned as a line.

The stash is represented by a structure containing:

```c
typedef struct s_stash
{
	char	*data;
	size_t	used;
	size_t	capacity;
}	t_stash;
```

* `data` points to the allocated memory containing the stored characters.
* `used` stores the number of valid characters currently stored.
* `capacity` stores the total allocated size.

### Reading process

When `get_next_line()` is called, a temporary buffer of `BUFFER_SIZE + 1` bytes is allocated.

The function then reads data using `read()`.

The data is appended directly to the stash instead of creating a new string containing the old stash and the new buffer.

The basic process is:

```text
read()
  ↓
buffer
  ↓
check available stash capacity
  ↓
grow stash if necessary
  ↓
append buffer to stash
  ↓
check for '\n'
  ↓
extract one line
  ↓
keep remaining data in stash
```

### Dynamic stash growth

The stash starts with no allocated memory. When more space is required, its capacity is increased.

The implementation starts with an initial capacity and doubles the capacity until it is large enough for:

```text
used + new bytes + 1
```

The additional byte is required for the terminating `'\0'`.

When the stash needs to grow:

1. A new larger memory block is allocated.
2. Existing stash data is copied into the new block.
3. The old memory is freed.
4. `stash->data` is updated to point to the new block.

This avoids allocating a new exact-sized string for every `read()` operation.

### Why this algorithm was selected

A simple implementation can use `ft_strjoin()` after every `read()`:

```text
stash + buffer → new allocation
```

However, this repeatedly copies all previously accumulated characters.

For example, with `BUFFER_SIZE=1` and a 10,000-character line, the implementation could repeatedly copy:

```text
1 + 2 + 3 + ... + 10,000
```

characters, resulting in quadratic (`O(n²)`) copying behavior.

The dynamic stash reduces this overhead by keeping allocated memory and appending new data directly to the unused portion of the stash.

The implementation also avoids repeatedly searching the entire stash for a newline. Once the existing stash is known not to contain a newline, the newly read buffer is checked for `\n`. This is particularly important for small `BUFFER_SIZE` values such as `1`.

This approach provides better performance for large lines while keeping the implementation compatible with the project restrictions.

### Returning a line

When a newline is found, `ft_get_line()` creates a new string containing the next line, including `\n` when present.

After the line is returned, `ft_update_stash()` moves the remaining unread characters to the beginning of the existing stash.

The allocated stash is therefore reused for subsequent calls.

```text
Before:

stash:
[hello\nworld\n42\0]
       ↑
     line ends

Return:
[hello\n]

Remaining stash:
[world\n42\0]
```

The stash remains allocated and can be reused for the next call.

## Instructions

### Compilation

The project can be compiled with a chosen `BUFFER_SIZE`:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c
```

For example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 \
get_next_line.c get_next_line_utils.c main.c
```

The implementation is also designed to work with large `BUFFER_SIZE` values.

### Usage

Example:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

Compile and run:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c

./a.out
```

`main.c` is only a testing file and is not required by the project subject.

## Resources

### Documentation

* `read(2)` — Linux manual page: explains reading bytes from a file descriptor.
* `malloc(3)` — Linux manual page: explains dynamic memory allocation.
* `free(3)` — Linux manual page: explains releasing dynamically allocated memory.
* `open(2)` — Linux manual page: explains opening files and obtaining file descriptors.

Useful command-line documentation:

```bash
man read
man malloc
man free
man open
```

### 42 Resources

* 42 `get_next_line` subject — project requirements, restrictions, and expected behavior.
* 42 Norminette documentation — coding style and Norm requirements.

### AI usage

AI was used as a learning and debugging assistant during the development of this project.

It was used for:

* Understanding the behavior of `read()`, `malloc()`, and `free()`.
* Understanding static variables and how data can persist between `get_next_line()` calls.
* Reasoning about the purpose of the stash and newline detection.
* Debugging memory-management problems using Valgrind output.
* Understanding and improving the performance problem caused by repeatedly joining the stash with newly read data.
* Designing and reasoning about the dynamic stash structure using `data`, `used`, and `capacity`.
* Checking the logic of helper functions and identifying possible edge cases.
* Understanding how to divide the implementation into functions while respecting the 42 Norm 25-line limit.
* Reviewing the README structure and explaining the selected algorithm.

AI was **not used as a replacement for understanding or testing the implementation**. The code was developed, tested, debugged, and verified manually using compilation, Valgrind, and the project tester.

## Testing

The implementation was tested with different `BUFFER_SIZE` values, including small and large values.

Tests included:

* Normal files containing multiple lines.
* Empty lines.
* Empty files.
* Files containing a single line.
* Files whose final line has no newline.
* Large lines.
* Large files.
* `BUFFER_SIZE=1`.
* Larger `BUFFER_SIZE` values.
* Invalid file descriptors.
* Repeated calls to `get_next_line()`.

Memory management was checked with Valgrind.

```bash
valgrind --leak-check=full --show-leak-kinds=all ./a.out
```
Example successful result:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts
```
