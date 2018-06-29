#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#define DEFAULT_NUM_ELEMENTS 10000000
#define USING_THREAD

int f( int threadNum, std::size_t numElements )
{
	std::cout << "f( threadNum = " << threadNum << ", numElements = " << numElements << " )" << std::endl;
	
	//	construct a vector that will containt a pointer to double
	//		we will allocate the double and store their pointer here
	std::vector<double *> doublePtrVector;
	
	//	allocate loop
	for( std::size_t i = 0 ; i < numElements ; ++ i )
	//	do an allocation and store
		doublePtrVector.emplace_back( new double );
	
	//	deallocate loop
	for( std::size_t i = 0 ; i < numElements ; ++ i )
	//	do an allocation and store
		delete doublePtrVector[i];
		
	std::cout << "DONE :: f( threadNum = " << threadNum << " )" << std::endl;
}

int main( void )
{
	std::cout << "main()" << std::endl;
	std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
#ifndef USING_THREAD
	//	call f()
	f();
#else
	//	using std::thread
	std::cout << "   starting f0 thread....." << std::endl;
	std::size_t numF0Elements = static_cast<int>( 1.25*DEFAULT_NUM_ELEMENTS );
	std::thread f0Thread( f, 0, numF0Elements );
	std::this_thread::sleep_for( std::chrono::seconds( 25 ) );

	std::cout << "   starting f1 thread....." << std::endl;	
	std::thread f1Thread( f, 1, DEFAULT_NUM_ELEMENTS );
	std::cout << "   starting f2 thread....." << std::endl;
	std::thread f2Thread( f, 2, DEFAULT_NUM_ELEMENTS );
	
	//	wait for join
	std::cout << "   waiting for all threads finished." << std::endl;
	f0Thread.join();
	f1Thread.join();
	f2Thread.join();

	std::cout << "   all threads finished." << std::endl;
	std::this_thread::sleep_for( std::chrono::seconds( 10 ) );

#endif
}
