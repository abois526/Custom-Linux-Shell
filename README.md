# Custom Linux Shell
A simple command-line interface shell built in C that supports basic Unix commands, pipelines, and I/O redirection.


## Project Overview
This project is a custom-built shell environment, emulating core features of a typical Linux shell. The shell provides a prompt to execute basic Unix commands, handle multi-stage pipelines, and redirect input/output. It also includes support for background job execution.

## Features
- **Command Execution**: Runs standard Unix commands.
- **Pipelines**: Supports multi-stage command pipelines using `|`.
- **I/O Redirection**: Implements input (`<`) and output (`>`) redirection.
- **Background Execution**: Allows background jobs using `&`.
- **Custom Error Handling**: Manages errors without using standard C library functions.
