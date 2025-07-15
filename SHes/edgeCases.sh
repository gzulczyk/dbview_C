#!/bin/bash

DB="../bin/test_dbview.db"
BIN="../bin/dbview"

echo "===> Cleaning up..."
rm -f "$DB"

echo "===> 1. Creating database header"
$BIN -f "$DB" -h || exit 1

echo "===> 2. Adding employees"
$BIN -f "$DB" -e "Alice Smith, Main St 1, 40" || exit 1
$BIN -f "$DB" -e "Bob Johnson, Second Ave 22, 30" || exit 1
$BIN -f "$DB" -e "Charlie Brown, Third Blvd 300, 20" || exit 1

echo "===> 3. Listing all employees"
$BIN -f "$DB" -a || exit 1

echo "===> 4. Reading employee by ID"
$BIN -f "$DB" -o 1 || exit 1  # should be Bob

echo "===> 5. Editing employee"
$BIN -f "$DB" -m "Bob Johnson, Second Ave 99, 35" -i 1 || exit 1

echo "===> 6. Reading employee after edit"
$BIN -f "$DB" -o 1 || exit 1

echo "===> 7. Removing employee"
$BIN -f "$DB" -d 0 || exit 1  # delete Alice

echo "===> 8. Listing employees after deletion"
$BIN -f "$DB" -a || exit 1

echo "===> 9. Reading database header"
$BIN -f "$DB" -r || exit 1

echo "✅ All tests completed successfully!"
