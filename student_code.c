#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>

void logStart(char* tID);//function to log that a new thread is started
void logFinish(char* tID);//function to log that a thread has finished its time

void startClock();//function to start program clock
long getCurrentTime();//function to check current time since clock was started
time_t programClock;//the global timer/clock for the program

typedef struct thread //represents a single thread
{
	char tid[4];//id of the thread as read from file
//add more members here as per requirement
	int tstart;
	int tend;
	pthread_t * ref;
} Thread;

void swap(Thread * a, Thread * b);

void* threadRun(void* t);//the thread function, the code executed by each thread
int readFile(char* fileName, Thread** threads);//function to read the file content and build array of threads

int main(int argc, char *argv[])
{
	if(argc<2)
	{
		printf("Input file name missing...exiting with error code -1\n");
		return -1;
	}



	Thread ** threadz;
	
	threadz = (Thread**) malloc(sizeof(Thread*));
        
        int count;	
	count = readFile(argv[1],threadz);


       //pthread_t  thread_id;     	       /* thread's ID (just an integer) */
       //pthread_t  thread_id;     	       /* thread's ID (just an integer) */

	int p = 0;
//threadz[0]->tstart
  //     pthread_t  main_thread;
	
	

	//int index_of_firsts[4];
	//int temp;
	// finding the first prosese first and then second and so on
	//
	//
	//



// Sorting the threads based on their arival time 
	
	for (int kk=0;kk<count;kk++){
		for (int qq=kk+1; qq<count; qq++){



			//if (  m[kk] > m[qq] ){
			//	temp = m[kk];
			//	m[kk] = m[qq];
			//	m[qq] = temp;
			//}
			//
	//		printf("%s \n","_____________");
	//		printf("kk:%s \n",((* threadz)[kk]).tid);
	//		printf("qq:%s \n",((* threadz)[qq]).tid);

			if ( ((* threadz)[kk]).tstart > ((* threadz)[qq]).tstart){
			//	 * dummy = & ((* threadz)[kk]);
			//	((* threadz)[kk]) = ((* threadz)[qq]);
			 //       ((* threadz)[qq]) = **dummy;	

				swap(&((* threadz)[kk]),&((* threadz)[qq]));

			}
			//else{
			//	* dummy = & ((* threadz)[qq]);
                         //       ((* threadz)[qq]) = ((* threadz)[kk]);
                          //      ((* threadz)[kk]) = **dummy;			
			//}
		
		}

		}

//	for (int g=0;g<3;g++){

//		printf("%d /n",m[g]);
//	}


	
startClock();	



	while (p < count){

	  
	 
	 while (getCurrentTime() != ((* threadz)[p]).tstart) {
	
	 	// Waiting until then
	 }


//	 while (getCurrentTime() != 1 && getCurrentTime() != 2 && getCurrentTime() != 3 && getCurrentTime() != 5 ) {
			// gotta wait until time arrives 
	 // gotta wait until time arrives 
//	  }


        pthread_t  thread_id;
        ((* threadz)[p]).ref = & thread_id; 
       pthread_create(& thread_id, NULL, (void *) threadRun , &((* threadz)[p]) ) ;
       p++;
//       pthread_join(thread_id,NULL);

// pthread_join(main_thread,NULL);   
//       if ( getCurrentTime() == ((* threadz)[p]).tend ){
//	       
  //     		pthread_join((pthread_t)((* threadz)[p]).tid,NULL) ;

//	       logFinish( ((* threadz)[p]).tid);
  //     }

	// THIS join here, cuz it to wait until the operation of new creted thread is finished.
	//	pthread_join(thread_id,NULL);    
     	}
	//pthread_join(main_thread,NULL);

	// Waiting until the longest (Gotta find longest) thread is Done

	pthread_join(*((* threadz)[count-4]).ref,NULL);
	pthread_join(*((* threadz)[count-3]).ref,NULL);
	pthread_join(*((* threadz)[count-2]).ref,NULL);
	pthread_join(*((* threadz)[count-1]).ref,NULL);

//	pthread_join(main_thread,NULL);
//printf("%s \n","Ooops");	

// *** WHy this solves the issue ? 
//sleep(6);

//	pthread_join(main_thread,NULL);

	    //you can add some suitable code here as per problem sepcification

	//while()//put a suitable condition here to run your program
	//{
	    //write suitable code here to run the threads
	//}
	return 0;
}

int readFile(char* fileName, Thread** threads)//use this method in a suitable way to read file
{
	FILE *in = fopen(fileName, "r");
	if(!in)
	{
		printf("Child A: Error in opening input file...exiting with error code -1\n");
		return -1;
	}

	struct stat st;
	fstat(fileno(in), &st);
	char* fileContent = (char*)malloc(((int)st.st_size+1)* sizeof(char));
	fileContent[0]='\0';	
	while(!feof(in))
	{
		char line[100];
		if(fgets(line,100,in)!=NULL)
		{
			strncat(fileContent,line,strlen(line));
		}
	}
	fclose(in);

	char* command = NULL;
	int threadCount = 0;
	char* fileCopy = (char*)malloc((strlen(fileContent)+1)*sizeof(char));
	strcpy(fileCopy,fileContent);
	command = strtok(fileCopy,"\r\n");
	while(command!=NULL)
	{
		threadCount++;
		command = strtok(NULL,"\r\n");
	}
	*threads = (Thread*) malloc(sizeof(Thread)*threadCount);

	char* lines[threadCount];
	command = NULL;
	int i=0;
	command = strtok(fileContent,"\r\n");
	while(command!=NULL)
	{
		lines[i] = malloc(sizeof(command)*sizeof(char));
		strcpy(lines[i],command);
		i++;
		command = strtok(NULL,"\r\n");
	}



	for(int k=0; k<threadCount; k++)
	{
		char* token = NULL;
		int j = 0;
		token =  strtok(lines[k],";");

		
		while(token!=NULL && j < 3)

			// j < 1 only oupt puts the first token of each line 
		{
		


		 // First Arg ( the tid ) 
		if (j == 0){	

			strcpy(((* threads)[k]).tid,& (* token));	

		}

	//	else if (j == 1) {
	//	(* threads[j]).tstart = (* token);
		if ( j == 1){
			(( * threads)[k]).tstart = atoi(token);
		}

		if ( j == 2) {

			(( * threads)[k]).tend = atoi(token);
		
		}
		j++;

		//Staying on the same line 
		
		token = strtok(NULL,";");
		
		}


		
//this loop tokenizes each line of input file
//write your code here to populate instances of Thread to build a collection
	}
	return threadCount;
}

void logStart(char* tID)//invoke this method when you start a thread
{
	printf("[%ld] New Thread with ID %s is started.\n", getCurrentTime(), tID);
}

void logFinish(char* tID)//invoke this method when a thread is over
{
	printf("[%ld] Thread with ID %s is finished.\n", getCurrentTime(), tID);
}

void* threadRun(void* t)//implement this function in a suitable way
{
//	printf("[%ld] New Thread with ID %d is started.\n", getCurrentTime(),0);
       // pthread_t thisThread;
        //thisThread = pthread_self();
       // pthread_join(thisThread,NULL);
	
//	pthread_join(main_thread,NULL)
	logStart(((Thread *) t)->tid);
	int duration =  ((Thread *) t)->tend ;
	//printf("%s \n","Sleeping Now...!");
	sleep(duration);
        //printf("%d \n",1);
	logFinish(((Thread *) t)->tid);
	  //      printf("%d \n",2);

//	pthread_t thisThread;
//	thisThread = pthread_self();
//	pthread_join(thisThread,NULL);
	pthread_exit(NULL);
	



	return 0;	
}

void startClock()//invoke this method when you start servicing threads
{
	programClock = time(NULL);
}

long getCurrentTime()//invoke this method whenever you want to check how much time units passed
//since you invoked startClock()
{
	time_t now;
	now = time(NULL);
	long j;
	j = now - programClock;
	return j;
}


void swap(Thread * a, Thread * b)
{
   Thread * temp;
   temp = (Thread*) malloc(sizeof(Thread));
   *temp = *b;
   *b = *a;
   *a = *temp;
}
