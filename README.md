# dbview

**dbview** is a simple low-level database viewer and editor for employee records.  
It is the final project required to complete the **low-level.academy** course titled **"Zero2Hero C Programming"**  
In this project, the student implements everything from scratch: from file creation to memory layout parsing and user input handling.

## Project Purpose

The purpose of `dbview` is to help students understand how to:

- Work with binary file structures and perform I/O operations using `open`, `read`, `write`, and `lseek`.
- Structure and validate custom file headers.
- Safely manage dynamic memory in C.
- Read, parse, and update structured binary data.
- Design a simple command-line tool with argument parsing.

## Features

### Create a New File
- Initializes a new database file with a binary header (`dbheader_t`) containing metadata such as magic bytes, version, entry count, and total file size.

### Validate File Type
When opening an existing file, the program:
- Reads and validates the header structure.
- Checks for the correct magic number and version.
- Verifies file integrity by comparing the file size in the header against the actual file size on disk.

### Read Employee Data
After validating the file, `dbview` reads employee entries:
- Each record includes `name`, `address`, and `hours worked`.
- Data is converted from network byte order to host byte order.

### Add New Employees
- Adds a new employee using a comma-separated string.
- Automatically reallocates memory to accommodate the new entry.
- Updates the header to reflect the new count and file size.

### Display Employees
- Displays all employee records in a human-readable format.
