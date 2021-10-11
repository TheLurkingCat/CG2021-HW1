#!/bin/bash
if [ $# -eq 1 ]; then
  echo "Packing for $1"
  zip -qr9 "HW1_$1.zip" include src
else
  echo "Usage: script/pack.sh <student_id>"
fi
