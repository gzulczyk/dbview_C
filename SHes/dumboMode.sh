#!/bin/bash

DB="../bin/test_dbview.db"
BIN="../bin/dbview"

echo "===> Cleaning up..."
rm -f "$DB"

# Trying to read, delete, and modify before the file even exists
echo "===> [DUMB] Try to read header from non-existent file"
$BIN -f "$DB" -r

echo "===> [DUMB] Try to delete employee from non-existent file"
$BIN -f "$DB" -d 0

echo "===> [DUMB] Try to read employee with insane ID"
$BIN -f "$DB" -o 999999

echo "===> [DUMB] Try to modify employee with negative ID"
$BIN -f "$DB" -m "Oops Negative, Wrong Way, 99" -i -42

echo "===> [DUMB] Try to modify employee with no data"
$BIN -f "$DB" -m "" -i 0

echo "===> [DUMB] Create header properly this time"
$BIN -f "$DB" -h || exit 1

echo "===> [DUMB] Add employee with good and bad data mixed"
$BIN -f "$DB" -e "Normal Guy, Main Street, 42"
$BIN -f "$DB" -e "MissingAge, Nowhere"
$BIN -f "$DB" -e "Too,Many,Commas,123,Oops"
$BIN -f "$DB" -e ", , "  # pure junk

echo "===> [DUMB] Try to edit with junk data"
$BIN -f "$DB" -m ",," -i 0

echo "===> [DUMB] Read all to see what survived"
$BIN -f "$DB" -a

echo "===> [DUMB] Try to delete everyone including out-of-bounds"
$BIN -f "$DB" -d 0
$BIN -f "$DB" -d 1
$BIN -f "$DB" -d 999
$BIN -f "$DB" -d -3

echo "===> [DUMB] Read employee after deletion"
$BIN -f "$DB" -o 0
$BIN -f "$DB" -o 1

echo "===> [DUMB] Final header check"
$BIN -f "$DB" -r
