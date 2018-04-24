/* Round Robin Scheduling Simulation*/

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////
/* Process Data Structure */
struct process {
int pid; /* Process ID */
int burst; /* CPU Burst Time */
int priority; /* Priority */
int working; /* Working time, for round-robin scheduling */
int waiting; /* Waiting time, for round-robin scheduling */
struct process *next;
};
//////////////////////////////////////////////////////////////////////////
/* Function Prototype Declarations */
struct process *init_process (int pid, int burst, int priority);
void listprocs (struct process *proc);
void rr (struct process *proc, int quantum);
//////////////////////////////////////////////////////////////////////////
/* Main Program Segment */
int main (void) {
/* Initialize process list */
struct process *plist, *ptmp;
plist = init_process(1, 10, 3);
plist->next = init_process(2, 1, 1); ptmp = plist->next;
ptmp->next = init_process(3, 2, 3); ptmp = ptmp->next;
ptmp->next = init_process(4, 1, 4); ptmp = ptmp->next;
ptmp->next = init_process(5, 5, 2);
////////////////////////////////////////////////////////////////////////// 
/* Perform simulations */
listprocs(plist);
rr(plist, 1);
/* Terminate cleanly */
while (plist != NULL) {
ptmp = plist;
plist = plist->next;
free(ptmp);
};
return(0);
};
////////////////////////////////////////////////////////////////////////// 
/* Process list entry initialization routine */

struct process *init_process (int pid, int burst, int priority) {
struct process *proc;
proc = malloc(sizeof(struct process));
if (proc == NULL) {
printf("Fatal error: memory allocation failure.\nTerminating.\n");
exit(1);
};
proc->pid = pid;
proc->burst = burst;
proc->priority = priority;
proc->working = 0;
proc->waiting = 0;
proc->next = NULL;
return(proc);
};
//////////////////////////////////////////////////////////////////////////
/* Process listing */
void listprocs (struct process *proc) {
struct process *tmp = proc;

printf("BEGIN:\tProcess Listing\n");

while (tmp != NULL) {
printf("PID: %d\t\tPriority: %d\tBurst: %d\n", tmp->pid, tmp->priority, tmp->burst);
tmp = tmp->next;
};

printf("END:\tProcess Listing\n\n");
}; 
//////////////////////////////////////////////////////////////////////////
/* Round-Robin scheduling simulation */
void rr (struct process *proc, int quantum) {
int jobsremain, passes;
struct process *copy, *tmpsrc, *tmp, *slot;

printf("BEGIN:\tRound-Robin scheduling simulation (Quantum: %d)\n", quantum);
/* Duplicate process list */
tmpsrc = proc;
copy = tmp = NULL;
while (tmpsrc != NULL) {
if (copy == NULL) {
copy = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
tmp = copy;
} else {
tmp->next = init_process(tmpsrc->pid, tmpsrc->burst, tmpsrc->priority);
tmp = tmp->next;
};
tmpsrc = tmpsrc->next;
};
//////////////////////////////////////////////////////////////////////////
/* Main routine */
jobsremain = 1;
slot = NULL;
while (jobsremain) {
jobsremain = 0;
//////////////////////////////////////////////////////////////////////////
/* Pick next working slot */
if (slot == NULL) {
slot = copy;
jobsremain = 1;
} else {
passes = 0;
do {
if (slot->next == NULL) {
passes++;
slot = copy;
} else {
slot = slot->next;
};
} while (passes <= 2 && slot->burst == slot->working);
if (passes <= 2) {
jobsremain = 1;
};
};
//////////////////////////////////////////////////////////////////////////
/* Perform a cycle */
tmp = copy;
while (tmp != NULL) {
if (tmp->burst > tmp->working) {
if (tmp == slot) {
tmp->working += quantum;
} else {
tmp->waiting += quantum;
};
};
tmp = tmp->next;
};
};
//////////////////////////////////////////////////////////////////////////
/* Display statistics and clean up copy */
tmp = copy;
while (tmp != NULL) {
printf("Process: %d\tWorking: %d\tWaiting: %d\tTurnaround: %d\n", 
tmp->pid, tmp->working, tmp->waiting, tmp->working + tmp->waiting);
tmpsrc = tmp;
tmp = tmp->next;
free(tmpsrc);
};

printf("END:\tRR scheduling simulation\n\n");
};
