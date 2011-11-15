#!/bin/bash
    find $1 -type f -iname \*.cc -or -iname \*.h -exec sh -c  "python cpplint.py  --filter=+build,-build/include,+readability,-readability/multiline_comment,-readability/function,+runtime,-runtime/int,-runtime/printf,-runtime/rtti,-whitespace --output=vs7 '{}'" \; 

