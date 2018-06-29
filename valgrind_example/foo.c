#include <stdlib.h>

// problem 1 - line 8 : heap block overrun
// problem 2 - line 9 : memory leak -- x not freed
void f( void )
{
	int *x = malloc( 10 * sizeof( int ) );
	x[10] = 0; 
}       

int main( void )
{
	f();
	return 0;
}
