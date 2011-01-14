///-----------------------------------------------------------------------
/// variable declarations
///-----------------------------------------------------------------------
// without initialization
int a, b, c;
//-----------------------------------------------------------------------
// with initialization
int a = 0;
int b = 1;
int c = 123;
//-----------------------------------------------------------------------
// pointer variables (always on separate lines)
char* d = "blah";
char* e = NULL;
char* f = d;
//-----------------------------------------------------------------------
// complex variable names
float a_complex_variable_name;
///-----------------------------------------------------------------------
/// expressions
///-----------------------------------------------------------------------
// arithmetic expressions
a = b + c - d * e / f;
//-----------------------------------------------------------------------
// binary expressions
a = (b | c) << 8 & d;
//-----------------------------------------------------------------------
// conditional expressions
(a == b) ? 1 : 2
// ... or ...
(a == b)?1:2
//-----------------------------------------------------------------------
// logical expressions
(a == b || (b == c && d == f))
///-----------------------------------------------------------------------
/// enumerations
///-----------------------------------------------------------------------
// ordered by values
enum SwitchCaseValues
{
	SCV_SimpleCase = 1, 
	SCV_SimpleMultiCase = 123, 
	SCV_AnotherCase = 456, 
	SCV_ComplexCase = 457, 
	SCV_ComplexMultiCase = 0x1000
};
//-----------------------------------------------------------------------
// ordered alphabetically (for automatically initialized enums)
enum SimpleEnum
{
	SE_Cat, 
	SE_Dog, 
	SE_Mouse
};
///-----------------------------------------------------------------------
/// functions / methods
///-----------------------------------------------------------------------
void func1() { /* a very simple function */ }
//-----------------------------------------------------------------------
void func2()
{ /* another very simple function */ }
//-----------------------------------------------------------------------
void func3()
{
	/*
	function with more complex code
	*/
}
///-----------------------------------------------------------------------
/// control flow
///-----------------------------------------------------------------------
// branches
if(a == b && a == c)
	func1();

else if(b == c || d == f)
{
	a++;
	func2();
	c = d - f;
}
else
	func3();
//-----------------------------------------------------------------------
// switch / case
switch(a)
{
case SCV_SimpleCase:
	func1();
	break;

case SCV_SimpleMultiCase:
case SCV_AnotherCase:
	func2();
	break;

case SCV_ComplexCase:
case SCV_ComplexMultiCase:
	{
		func3();
		c++;
	}
	break;

default:
	simpleDefault();
	break;
};
//-----------------------------------------------------------------------
