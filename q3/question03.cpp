// Question 3 - implementation
// 
//	without using STL containers implement the following:
//	A class for a dynamic int array, let's call it "CVectorInt" that -
//  1. doubles its size automatically when its full (allocates twice the size and moves the data),
//	2. halves its size when it is half empty (allocates half of the size and moves the data)
//  3. can be told the initial capacity (num of ints) in a constructor
//  4. have a method called "reserve" - that Requests that the vector capacity be at least enough to contain n elements.
//     If n is greater than the current vector capacity, the function causes the container to reallocate its storage increasing its capacity to n
//  5. have a method called "capacity" - that returns the number of int elements allocated
//  6. have a method called "size" - that returns the number of elements actually inserted
//  7. have a method called "empty" - that returns true/false according to amount of actual elements in the data
//  8. have a method called "clear" - that frees all the data and resets the size
//  9. have a method called "push_back" - that adds an int elements at the end
// 10. have a method called "pop_back" - that removes an int elements at the end and return it
// 11. have a method called "remove"  - that removes an int elements at specific index
// 12. have an interface to access the data at a specific index using subscript "[]"
//
// make sure to handle edge cases such as memory issues, size issues etc.



#include <iostream>
#include <stdexcept>

#define VEC_DEFAULT_CAPACITY       10
#define VEC_SPAIR_ELEMENTS         2
#define VEC_UNDEFINE_BEHAVIOR_INT  INT_MIN

class CVectorInt
{
public:
    CVectorInt(size_t n = VEC_DEFAULT_CAPACITY);
    CVectorInt(const CVectorInt& other);
    
    ~CVectorInt();
    CVectorInt& operator=(const CVectorInt& other);
    
    int  pop_back();
    void push_back(int);

    void clear();
    void remove(int);
    void reserve(int);

    bool   empty()    const;
    size_t capacity() const;
    size_t size()     const;
    
    int& operator[](int);

private:
    void reallocData(size_t);
    void validateMem(int*);

private:
    size_t  mSize;
    size_t  mCapacity;
    int*    mData;
};


CVectorInt::CVectorInt(size_t n)  
    : mSize(0), 
      mCapacity(n)
{
    if(n <= 0)
        throw std::runtime_error("cannot create CVectorInt with negative value");

    mData = new int[n];

    validateMem(mData);
}

CVectorInt::CVectorInt(const CVectorInt& other)
    : mSize(other.mSize),
      mCapacity(other.mCapacity),
      mData(new int[mCapacity])
{
    validateMem(mData);

    for(size_t i = 0; i < other.mSize; i++)
        mData[i] = other.mData[i];
}

CVectorInt::~CVectorInt()
{
    delete[] mData;
}

CVectorInt& CVectorInt::operator=(const CVectorInt& other)
{
    if(this == &other)
        return *this;
        
    if(other.mSize > mSize)
    {
        delete mData;
        mCapacity = other.mSize + VEC_SPAIR_ELEMENTS;
        mData = new int[mCapacity];
        validateMem(mData);
    }

    for(size_t i = 0; i < other.mSize; i++)
        mData[i] = other.mData[i];
    
    mSize = other.mSize;

    return *this;
}

void CVectorInt::push_back(int val)
{
    if(mSize < mCapacity)
    {
        mData[mSize] = val;
        mSize++;
    }
    else
    {
        reallocData(mCapacity*2);

        mData[mSize] = val;
        mSize++;
    }
}

int CVectorInt::pop_back()
{
    if(mSize == 0)
        return VEC_UNDEFINE_BEHAVIOR_INT;

    if(mSize <= mCapacity/2)
        reallocData(mCapacity/2);
    
    mSize--;
    return mData[mSize];
}

void CVectorInt::clear()
{
    int* newData = new int[VEC_DEFAULT_CAPACITY];
    validateMem(newData);

    delete[] mData;
    
    mData = newData;
    mSize = 0;
}

void CVectorInt::remove(int idx)
{
    if(idx < 0 || idx >= mSize)
        throw std::runtime_error("remove() index out of bounds");
    
    for(size_t i = idx; i < mSize-1; i++)
        mData[i] = mData[i+1];
    
    mSize--;
}

void CVectorInt::reserve(int n)
{
    if(mCapacity >= n)
        return;

    reallocData(n + VEC_SPAIR_ELEMENTS);
}

void CVectorInt::reallocData(size_t capacity)
{
    mCapacity = capacity;
    
    int* newData = new int[mCapacity];
    validateMem(newData);
    
    for(size_t i = 0; i < mSize; i++)
        newData[i] = mData[i];
    
    delete[] mData;
    mData = newData;
}

int& CVectorInt::operator[](int i)
{
    return mData[i];
}

bool CVectorInt::empty() const
{
    return mSize == 0;
}

size_t CVectorInt::size() const
{
    return mSize;
}

size_t CVectorInt::capacity() const
{
    return mCapacity;
}

void CVectorInt::validateMem(int *mem)
{
    if(!mem)
        throw std::runtime_error("Failed to acquire memory");
}



int main(int argc, char* argv[])
{
	// some code to use the class
	try
	{
        CVectorInt v(5);

		for (int i = 0; i < 5; i++)
		{
			v.push_back(i);
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.push_back(1);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		while (!v.empty())
		{
			v.pop_back();
		}
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		v.reserve(15);
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
		{
			v.push_back(i);
		}
		v[5] = 3;
		for (int i = 0; i < v.size(); i++)
		{
			std::cout << v[i] << " ";
		}
		std::cout << std::endl;
		v.clear();
		std::cout << "the size is: " << v.size() << std::endl;
		std::cout << "the capacity is: " << v.capacity() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
    return 0;
}
