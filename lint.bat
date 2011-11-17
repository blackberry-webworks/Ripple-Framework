@echo off   
python cpplint.py --filter=+build,-build/include,+readability,-readability/multiline_comment,-readability/function,+runtime,-runtime/int,-runtime/printf,-runtime/rtti,-whitespace/braces,-whitespace/line_length,-whitespace/comments,-whitespace/parens,-whitespace/labels --output=vs7 %1 %2

if errorlevel 1 exit /b  1


