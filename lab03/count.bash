#!/bin/bash

#Suin Kim

for f in `ls`; do
  lines=`wc -l $f | cut -f1 -d' '`
  words=`wc -w $f | cut -f1 -d' '`
  echo "$f $lines $words"
done

exit 0
