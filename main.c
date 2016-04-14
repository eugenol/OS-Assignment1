/*
Operating Systems assignment

*/

/*
1. Read all processes into linked list
2. switch to right algorithm
3. 

*/

struct _data {
    int start_time;
    int run_time;
    struct _data *next;  
};

struct _process {
	char ID[11];
	int arrival;
	int burst;
	int priority;
    struct _data *time_data;
    struct _process *next;
};

int main(int argv, char **argv)
{
	// Parse Arguments
	// Read in input file
	// Store in a list all the inputs
	// Run simulation, depending on choice
	// Display results
	FILE *fptr;
	int scheduler;
	int quantum;	
		
	if (argv < 3)
	{
		printf("Usage is: sheduler <input file> <Scheduler> <quantum (optional)>")
		return EXIT_FAILURE;
	}
	
    
    
	fptr = fopen();	
	
	
	return 0;	
}