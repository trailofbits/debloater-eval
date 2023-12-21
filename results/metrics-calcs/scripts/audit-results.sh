#!/bin/bash
# examine:
# the details of every crash/report
# the stderr of every original run
# the ouput of any concurrent scripts
BINPATH=$1
find $BINPATH -name "report*.yml" -exec grep -H details {}  ";" | less
find $BINPATH -name "crash*.yml" -exec grep -H details {}  ";" | less
# only look at non-empty stderr files
find $BINPATH -path "*__original__*stderr*" -size +0 -exec less {}  ";"
find $BINPATH -path "*__original__*concurrent-output.bin" -size +0 -exec less {}  ";"
