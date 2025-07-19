#!/bin/bash

# ------------------------------------------------------------------------------
# Disclaimer:
# This tests doesn't make the program 100% bulletproof.
# I just wanted to use Valgrind in practice and see how does it debug (it does really good job!)
# ------------------------------------------------------------------------------

DB="../bin/test_dbview.db"
BIN="../bin/dbview"

run_vg() {
    echo
    echo "==> Running under Valgrind: $*"
    valgrind --leak-check=full --track-origins=yes --error-exitcode=99 "$@" || {
        echo "Valgrind detected a memory issue. Aborting."
        exit 1
    }
}

echo "===> Cleaning up..."
rm -f "$DB"

echo "===> 1. Creating database header"
run_vg $BIN -f "$DB" -h

echo "===> 2. Adding employees"
run_vg $BIN -f "$DB" -e "Alice Smith, Main St 1, 40"
run_vg $BIN -f "$DB" -e "Bob Johnson, Second Ave 22, 30"
run_vg $BIN -f "$DB" -e "Charlie Brown, Third Blvd 300, 20"

echo "===> 3. Listing all employees"
run_vg $BIN -f "$DB" -a

echo "===> 4. Reading employee by ID"
run_vg $BIN -f "$DB" -o 1 

echo "===> 5. Editing employee"
run_vg $BIN -f "$DB" -m "Bob Johnson, Second Ave 99, 35" -i 1

echo "===> 6. Reading employee after edit"
run_vg $BIN -f "$DB" -o 1

echo "===> 7. Removing employee"
run_vg $BIN -f "$DB" -d 0  

echo "===> 8. Listing employees after deletion"
run_vg $BIN -f "$DB" -a

echo "===> 9. Reading database header"
run_vg $BIN -f "$DB" -r

echo "===> 10. Remove undefined ID"
run_vg "$BIN" -f "$DB" -o 999

echo "===> 11. Try to add employee with broken syntax declaration"
run_vg "$BIN" -f "$DB" -e "IncompleteInputOnlyName"

echo "===> 12. Read with minus ID"
run_vg "$BIN" -f "$DB" -o -1

echo "===> 13. Try to operate on fakeFile"
run_vg "$BIN" -f "/fake/path/doesnotexist.db" -a

echo "All Valgrind tests completed successfully."
