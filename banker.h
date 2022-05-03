/* declarations related to banker's algorithm */
#ifndef BANKER_H_
#define BANKER_H_

void isSafe(int *available, int **alloc, int **need, int numThreads, int numResources);
void findAllSafe(int *work, int *safe, int *finish, int numFinished);

#endif /* BANKER_H_ */