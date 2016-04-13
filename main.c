/*
Operating Systems assignment

*/

struct _process {
	char ID[11];
	int arrival;
	int burst;
	int priority;
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
	
		
	
	
	return 0;	
}