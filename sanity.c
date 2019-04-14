#include "types.h"
#include "user.h"
int ind, time, delay;
int pidWait;
int proc[20];
int wtime, rtime, iotime, status;
int wTimeSum=0, rTimeSum=0, aTimeSum=0;

int computeDelay(int i) {
	if (i >= 10){
	    return 1000000;
	}
	else{
	    return 5000000;
	}
}

int main(){
	// create 20 processes
	for(ind = 0; ind < 20; ++ind){
	    proc[ind] = fork();
	    if(proc[ind] > 0){
	    	continue;
	    }
	    if(proc[ind] == -1){
	      printf(1, "Fail to fork.");
	      exit();
	    }
	    delay = computeDelay(ind);
	    for(time = 0; time < delay; time++){}
	    exit();
	}
	while((pidWait = wait_stat(&wtime, &rtime, &iotime, &status)) != -1){
	    for(ind = 0; ind < 20; ++ind){
	    	if(status == proc[ind]){
		        printf(1, "Child process: %d \npid %d:\n", ind, proc[ind]);
		        printf(1, "Wait time: %d,\nRun time: %d,\nTurnaround time: %d\n\n", wtime, rtime, wtime + rtime+ iotime);
		        break;
	      }
	    }
	    wTimeSum += wtime;
	    rTimeSum += rtime;
	    aTimeSum += (wtime + rtime + iotime);
	}
	printf(1, "Average waiting time is %d clock ticks.\n", wTimeSum / 20 );
	printf(1, "Average runtime is %d clock ticks.\n", rTimeSum / 20);
	printf(1, "Average turnaround time is %d clock ticks.\n", aTimeSum / 20);
	exit();
}
