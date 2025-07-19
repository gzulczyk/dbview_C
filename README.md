# dbview_C

A simple C-based binary database viewer and editor for employee records.

This is an unnecessary project required to pass the Zero2Hero C Programming course provided by low-level.academy.

## Features

- Create and validate database files
- Add, read, edit, and delete employee records
- Manual memory and file structure management


## Usage
```bash
# Create a new database
./dbview -f employees.db -h

# Add new employees
./dbview -f employees.db -e "Alice Smith, Main Street 1, 40"
./dbview -f employees.db -e "Bob Johnson, Second Ave 22, 30"

# List all employees
./dbview -f employees.db -a

# View an employee by ID
./dbview -f employees.db -o 1

# Edit an employee by ID
./dbview -f employees.db -m "Bob Johnson, Updated Address, 35" -i 1

# Delete an employee by ID
./dbview -f employees.db -d 0

# Read database header
./dbview -f employees.db -r

./dbview --help       # Show usage instructions
./dbview --features   # List all features
./dbview --version    # Show version
```