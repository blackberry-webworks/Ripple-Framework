#!/bin/bash
python cpplint.py --filter=+build,-build/include,+readability,-readability/multiline_comment,-readability/function,+runtime,-runtime/int,-runtime/printf,-runtime/rtti,-whitespace/line_length,-whitespace/comments,-whitespace/labels --output=vs7 $1 $2
