#!/bin/bash
    find $1 -type f -iname \*.cc -or -iname \*.h -exec sh -c  "python cpplint.py --filter=+build,+readability,+runtime,-whitespace --output=vs7 '{}'" \; 

