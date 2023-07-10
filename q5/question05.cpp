// Question 5
//
//	we want to implement a logic class named MyBool to use in our logic
//	we would like to be able to use the logical and (&&) with instances of this class 
//  i.e. to be able to write in the form of myBool1 && myBool2
//	we have also implemented some function using this class
//	"notNull" checks if a pointer is null and return a corresponding MyBool
//  "greaterThanZero" checks if an int pointer points to a positive int and 
//   return a corresponding MyBool
//
//	1. Implement this addition in the MyBool class
//  2. Did it compile successfully?
//	3. Did it run successfully?
//	4. Explain the result, explain what happened and why
//
// useful links:
// https://en.cppreference.com/w/cpp/language/operators
// https://cplusplus.com/doc/tutorial/operators/
// https://isocpp.org/wiki/faq/operator-overloading


/*
Answers:
	Added implementation for operator bool().
	To avoid illegal operation on MyBool (such as << and +) we have to make it an explicit operation.
	for example, an implicit operator allows: 
		MyBool b(true);
		int i = b; 
		b << 3;

	That conversion makes no sense, and more important it violates type safety.
	so, we have to make it explicit.
	
*/
 
#include <iostream>

class MyBool
{
public:
	MyBool(bool b) : m_val(b) {}

    explicit operator bool() const { return m_val; }
	//operator bool() const { return m_val; }

private:
	bool m_val;
};



MyBool notNull(int* intPtr)
{
	return intPtr != nullptr;
}

MyBool greaterThanZero(int* intPtr)
{
	return *intPtr > 0;
}

int main(int argc, char* argv[])
{
	int* a = nullptr;
	int val = 5;
	int* b = &val;
	
	// the long way to check
	if (a != nullptr && *a > 0)
	{
		++*a;
		std::cout << "*a is " << *a << std::endl;
	}

	// using our functions
	if (notNull(b) && greaterThanZero(b))
	{
		++*b;
		std::cout << "*b is " << *b << std::endl;
	}

	// using our functions again
	if (notNull(a) && greaterThanZero(a))
	{
		++*a;
		std::cout << "*a is " << *a << std::endl;
	}

	return 0;
}
