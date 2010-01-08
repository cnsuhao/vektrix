java -ea -DAS3 -DAVMPLUS -classpath %CASPIN_HOME%\tamarin\utils\asc.jar macromedia.asc.embedding.ScriptCompiler -out %1 -builtin -import %CASPIN_HOME%\tamarin\core\builtin.abc %2 %3 %4 %5 %6

@ECHO OFF
del *.h
del *.cpp

::-import %CASPIN_HOME%\tamarin\core\builtin.abc
::-apiversioning 