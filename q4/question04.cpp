//Question 4 - pointers

// There is a memory leak in the code below, where is it?, 
// what class/solution can you use to fix it while ensuring that the object 
// will be deleted only once and only when it's not used by any consumer

// Task: Modify the code to address the issues above. 
// Please explain the changes you made and how they solve the memory allocation/deletion issue  

// Do not remove any function or change threads dispatching order - 
// you can(and should) change the functions body/signature

/*
Answer:
	The memory leak is when creating Payload pointer, but not releasing it (in dispacher_thread()).
	To fix it we can use smart pointer. 
	Changes I made: - Payload* payload is now a shared_ptr (in dispacher_thread()).
					- operation1() and operation2() gets a shared_ptr as parameter.
		
		The Payload object will be deleted only after all the shares pointers 
		(which are created when passing it to operation1 and operation2) that point at it will be deleted.
*/

#include <chrono>
#include <iostream>
#include <vector>
#include <thread>
#include <random>
#include <memory>


struct Payload {

	Payload(uint64_t id_) :
		id(id_),
		veryLargeVector(1000*1000)
	{}

	uint64_t id;
	std::vector<int> veryLargeVector;
};

void operation1(std::shared_ptr<Payload> payload) {
	std::cout << "Performing operation1 on payload " << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1))));  //Simulate some heavy work
	std::cout << "Operation1 Performed" << std::endl;
}

void operation2(std::shared_ptr<Payload> payload) {
	std::cout << "Performing operation2 on payload "  << payload->id << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(std::chrono::seconds(5 + (std::rand() % (12 - 5 + 1)))));  //Simulate some heavy work
	std::cout << "Operation2 Performed" << std::endl;
}

void dispacher_thread() {
    std::shared_ptr<Payload> payload = std::make_shared<Payload>(1);
	std::this_thread::sleep_for(std::chrono::seconds(2));  //Simulate some heavy work
	std::thread wt1(&operation1, payload);
	std::thread wt2(&operation2, payload);
	//Waiting for wt1 & wt2 to finish is not allowed, dispacher_thread should exit after creating wt1 and wt2
	wt1.detach();
	wt2.detach();
}

int main(int argc, char** argv)
{
	std::cout << "Calling dispatcher thread" << std::endl;
	std::thread t(&dispacher_thread);
	t.join();

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}
