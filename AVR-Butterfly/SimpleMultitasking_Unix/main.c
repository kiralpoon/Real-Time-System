#include <stdio.h>
#include <setjmp.h>
#include <inttypes.h>
#include <unistd.h>


volatile uint32_t counter = 0;

jmp_buf task1_jb;
jmp_buf task2_jb;

void task1( void );
void task2( void );
void task2_tramp( void );

void
task1( void )
{
  for(;;)
    {
      if ( setjmp( task1_jb ) == 0 )
	{
	  task2_tramp();
	}
      else
	{
	  int scramble[200];
	  for(int i = 0; i < sizeof(scramble)/sizeof(scramble[0]);++i)
	    {
	      scramble[i] = i;
	    }
	  counter++;
	  printf("Task1 %d %d\n", counter, scramble[12] );
	  sleep(2);
	  longjmp( task2_jb, 1 );
	}
    }
}


void
task2_tramp(void)
{
  int hole[600];
  for(int i = 0; i < sizeof(hole)/sizeof(hole[0]); ++i )
    {
      hole[i] = i;
    }
  task2();
}

void
task2( void )
{
  int scramble[200];
  for(int i = 0; i < sizeof(scramble)/sizeof(scramble[0]);++i)
    {
      scramble[i] = i + 1000;
    }
  for(;;)
    {
      if ( setjmp( task2_jb ) == 0 )
	{
	  longjmp(task1_jb, 2);
	}
      else
	{
	  for(int i = 0; i < sizeof(scramble)/sizeof(scramble[0]);++i)
	    {
	      if ( scramble[i] != i + 1000 )
		{
		  printf("Scrambled %d %d\n", i, scramble[i] );
		  break;
		}		
	    }	  
	  counter++;
	  printf("Task2 %d\n", counter );
	  sleep(2);
	  longjmp( task1_jb, 1 );
	}
    }
}


int
main( int argc, char * argv[] )
{
  task1();
  return 0;
}
