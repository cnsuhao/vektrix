python %CASPIN_HOME%\tamarin\utils\nativegen.py %CASPIN_HOME%\tamarin\core\builtin.abc %2 %3 %4 %5 %6 %7 %8 %9 %1.abc

@ECHO OFF

move %1.cpp2 ..\src\%1.cpp
move %1.h2 ..\include\%1.h