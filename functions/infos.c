#include <stdio.h>
#include <unistd.h>
#include <string.h>

void printLogo() {
    printf("\n");
    printf("========================================\n");
    printf("              dbview_C v1.0            \n");
    printf("     low-level.academy :: Zero2Hero     \n");
    printf("========================================\n");
    printf("\n");
}



void printDescription() {
    printf(
        "\nA simple low-level database viewer and editor for employee records.\n"
        "This is the final project required to complete the low-level.academy course\n"
        "Zero2Hero C Programming, more info at \033[4mhttps://lowlevel.academy/courses/zero2hero/\033[0m\n"
        "In this project, the student implements everything from scratch: file creation,\n"
        "binary layout parsing, memory management, and command-line interfaces.\n"
    );
}

void printUsage() {
    printf(
        "USAGE:\n"
        "  ./dbview -f <db_file> <command> [options]\n"
        "  ./dbview -h                     Create a new database header\n"
        "  ./dbview -a                     List all employee records\n"
        "  ./dbview -e \"Name, Addr, Hrs\"    Add a new employee\n"
        "  ./dbview -m \"Name, Addr, Hrs\" -i <id>  Edit employee by ID\n"
        "  ./dbview -d <id>                Delete employee by ID\n"
        "  ./dbview -o <id>                View single employee by ID\n"
        "  ./dbview -r                     View file header info\n"
        "  ./dbview --help                 Display help command\n"
        "  ./dbview --features             Display features of this program\n"
        "  ./dbview --version              Display exact version of this app\n"
    );
}

void printFeatures() {
    printf("PROJECT PURPOSE:\n");
    printf("  - Understand binary file structure and use of open(), read(), write(), lseek()\n");
    printf("  - Create and validate custom binary headers\n");
    printf("  - Manage dynamic memory in C safely\n");
    printf("  - Parse and manipulate structured binary data\n");
    printf("  - Build a simple command-line interface with argument parsing\n\n");

    printf("FEATURES:\n");
    printf("  Create a New File:\n");
    printf("    - Initializes a database with a header structure (dbheader_t)\n");
    printf("    - Header includes magic number, version, filesize, record count\n\n");

    printf("  Validate File Type:\n");
    printf("    - Confirms correct magic/version\n");
    printf("    - Ensures file size matches expected value\n\n");

    printf("  Read Employee Data:\n");
    printf("    - Parses employee records: name, address, hours\n");
    printf("    - Converts byte order if necessary\n\n");

    printf("  Add New Employees:\n");
    printf("    - Accepts input as: \"Name, Address, Hours\"\n");
    printf("    - Reallocates memory and updates file structure\n\n");

    printf("  Display Employees:\n");
    printf("    - Prints all records in a readable format\n\n");
}

int printWhatYouExactlyWant(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 )
        {
            printDescription();
            printf("\n");
            printf("\n");
            printUsage();
            return 1;
        }
        else if (strcmp(argv[i], "--features") == 0) {
            printFeatures();
            return 1;
        }
        else if (strcmp(argv[i], "--version") == 0) {
            printf("dbview_C v1.0 (%s %s)\n", __DATE__, __TIME__);
            return 1;
        }
    }
    return 0;
} 