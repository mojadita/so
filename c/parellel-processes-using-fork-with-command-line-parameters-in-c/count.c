/* YOU NEED TO POST COMPLETE, COMPILABLE CODE, DON'T TAKE OFF
 * YOUR INCLUDE FILES TO POST, AS SOME ERRORS CAN COME FROM THE
 * FACT THAT YOU HAVE FORGOTTEN TO #include THEM.  */
#include <assert.h> /* for assert */
#include <stdio.h>  /* for printf and stdio functions */
#include <stdlib.h> /* for atoi */
#include <unistd.h> /* for getpid() */

int main(int argc, char** argv)
{
   assert(argc == 2);

   int length= atoi(argv[1]); 
   assert(length>0);

   int pid = getpid(); 

   printf("%d : %s\n", pid, "start");

   for (unsigned int i=length; i>0; i--)
   {
      printf("%d : %d\n", pid, i);

      sleep(1); 
   }

   printf("%d : %s\n", pid, "done");

   return 0;
}
