*This project was created as part of the 42 curriculum by sabahmad.*

# Get Next Line

## Description

**Get Next Line (GNL)** is a 42 project that involves implementing a function capable of reading from a file descriptor and returning one line at a time.

The function returns the line including the newline character (`\n`) when one is present. If the end of the input is reached and the remaining content does not end with a newline, the function returns the last line as it is. When there is no more content to read, or an error occurs, it returns `NULL`.

The main goal of this project is to understand file descriptors, the `read()` system call, static variables, dynamic memory allocation, and string manipulation in C.

## Instructions

### Compilation

Compile the source files together with a test file containing a `main()` function:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 \
get_next_line.c get_next_line_utils.c main.c -o gnl
```

Run the executable:

```bash
./gnl
```

The `BUFFER_SIZE` determines how many bytes are read in each call to `read()`. It can be changed during compilation to test the function with different buffer sizes.

## Algorithm

The implementation uses a **static stash** to store data read from the file descriptor and preserve any remaining content between calls.

The algorithm is divided into four main steps:

1. **`readstash()`** reads chunks of data using `read()` until a newline is found or the end of the input is reached. Each chunk is appended to the stash so that incomplete lines can be completed by subsequent reads.

2. **`extract()`** searches the stash for the next newline and extracts the corresponding line. The newline character is included when present.

3. **`modify()`** updates the stash after a line has been extracted. It removes the returned line and keeps the remaining content for the next function call. If no content remains, the stash is freed.

4. **`get_next_line()`** coordinates the process. It validates the arguments, manages the static stash, calls the helper functions, and returns the next line or `NULL` when appropriate.

Using a static variable allows the stash to retain its value between function calls. This prevents unread data from being lost when a single `read()` retrieves more data than is needed for the current line.


## Resources

- https://www.codequoi.com/en/local-global-static-variables-in-c/
- https://blogs.learningdevops.com/deep-dive-understanding-the-read-system-call-from-file-descriptors-to-data-flow-ed090d42c613

## AI Usage

ChatGPT was used as a learning aid to understand file descriptors, the `read()` system call, static variables, memory management, and debugging concepts.

## Author

**Seba Al-Sayed**

**42 Irbid — Common Core**

**Project: Libft**
