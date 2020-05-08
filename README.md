# IN4200-project2
Second project in IN4200 - High Performance Computing at the University of Oslo.

## Compiling
* Run "make clean all" for a clean build or just "make"

## Structure
* utils.c: Utility functions shared by serial and parallel implementation
* count_friends_of_ten.c: Serial implementation of algorithm
* mpi_count_friends_of_ten.c: MPI implementation of same algorithm.

## Note: As no custom headers are used, all headers needed in utils.c, count_friends_of_ten.c and mpi_count_friends_of_ten.c must be included in the main programs. 
