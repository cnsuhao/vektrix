///-----------------------------------------------------------------------
/// namespaces
///-----------------------------------------------------------------------
namespace A { namespace B {
	//-----------------------------------------------------------------------
	class SimpleClass
	{
		// ... members ...
	};
	//-----------------------------------------------------------------------
}}
//-----------------------------------------------------------------------
namespace A
{
	class AnotherClass
	{
		// ... members ...
	};
}
///-----------------------------------------------------------------------
/// class declarations
///-----------------------------------------------------------------------
// simple class
class SimpleClass
{
	// ... members ...
};
//-----------------------------------------------------------------------
// single inheritance
class DerivedClass : public BaseClass
{
	// ... members ...
};
//-----------------------------------------------------------------------
// multiple inheritance
class MultipleInheritance : 
	public FirstBase, 
	public SecondBase, 
	public ThirdBase
{
	// ... members ...
};
//-----------------------------------------------------------------------
// ... alternatively ...
class MultipleInheritance : public FirstBase, public SecondBase, public ThirdBase
{
	// ... members ...
};
///-----------------------------------------------------------------------
/// class members / accessors & mutators
///-----------------------------------------------------------------------
class ClassMembers
{
public:
	// publicly accessible attributes
	int any_attribute;

	// accessors / mutators
	void setAnyMember(const int& any_member);
	const int& getAnyMember() const;

	static void setAnotherMember(const float& another_member);
	static const float& getAnotherMember() const;

	void setPointerMember(char* pointer_member);
	char* getPointerMember() const;

protected:
	// protected attributes
	int mAnyMember;
	static float mAnotherMember;
	char* mPointerMember;
};
///-----------------------------------------------------------------------
/// class members operators
///-----------------------------------------------------------------------
// member operator
SimpleClass inst;
inst.func1();
//-----------------------------------------------------------------------
// member operator (reference)
SimpleClass& ref = inst;
ref.func1();
//-----------------------------------------------------------------------
// member operator (pointer)
SimpleClass* ptr = &inst;
ptr->func1();
//-----------------------------------------------------------------------
