#include <stdio.h>
#include <stdlib.h>
#include <libproc.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <mach/mach_time.h>


#define ORWL_NANO (+1.0E-9)
#define ORWL_GIGA UINT64_C(1000000000)

struct timespec clock_gettime(void) {
  // be more careful in a multithreaded environement
  struct timespec t;
  double time = mach_absolute_time();
  t.tv_sec = time * ORWL_NANO;
  t.tv_nsec = time - (t.tv_sec * ORWL_GIGA);
  return t;
}


double diffclock(struct timespec a,struct timespec b)
{
	return ((double)b.tv_sec + ORWL_NANO*b.tv_nsec - (double)a.tv_sec + ORWL_NANO*a.tv_nsec);

}

int main(int argc, char const *argv[])
{
	// while(1)
	// {
	// 	struct timespec tstart={0,0}, tend={0,0};
	// 	clock_gettime(CLOCK_REALTIME, &tstart);
	// 	clock_gettime(CLOCK_REALTIME,&tend);
	// 	//printf("on démarre\n\n");
	// 	while( diffclock(tstart, tend)/1000 <= 1 ){
	// 		//printf("%f\n",diffclock(tstart, tend)/1000);
	// 		//printf("difftime: %f\n",difftime(end_t, start_t));
	// 		clock_gettime(CLOCK_REALTIME,&tend);
	// 		//printf("%ld, %ld, %f \n",start_t, end_t, difftime(end_t, start_t)/1000.0 );
	// 	}
	// 	//printf("fin de la boucle while\n");
	// 	usleep(4000);
	// 	//printf("fin du sleep\n");

	// }
	while(1)
	{
		clock_t tstart, tend;
		tstart = tend = clock();
		//printf("on démarre\n\n");
		while( (double)(tend - tstart)/CLOCKS_PER_SEC <= 0.0004 ){
			//printf("%f\n",(double)(tend - tstart) );
			//printf("%f\n",diffclock(tstart, tend)/1000);
			//printf("difftime: %f\n",difftime(end_t, start_t));
			tend = clock();
			//printf("%ld, %ld, %f \n",start_t, end_t, difftime(end_t, start_t)/1000.0 );
		}
		//printf("fin de la boucle while\n");
		usleep(1600);
		//printf("fin du sleep\n");

	}
	

	return 0;
}