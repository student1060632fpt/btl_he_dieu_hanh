#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
	/* TODO: put a new process to queue [q] */
	// queue đầy thì ko enqueue
	if (q->size == MAX_QUEUE_SIZE) {}

	// tìm vị trí chèn
	for (int i = 0; i<MAX_QUEUE_SIZE; i++) {
		if (proc->priority < q->proc[i]->priority) {
			//dời vị trí các phần tử bắt đầu từ i về sau 1 vị trí
			for(int j=MAX_QUEUE_SIZE; j > i; j--) {
				q->proc[j] = q->proc[j-1];
			}
			//nhét phần tử proc vào vị trí i
			q->proc[i] = proc;
		}
	}
	// tăng size của queue
	q->size+=1;
}

struct pcb_t * dequeue(struct queue_t * q) {
	/* TODO: return a pcb whose prioprity is the highest
	 * in the queue [q] and remember to remove it from q
	 * */
	if(empty(q)) {
		return NULL;
	} else {
		// find the smalest priority and index of the first smalest priority
		// int priority = q->proc[0]->priority;
		// int index_pri = 0;
		// for(int i =1; i<q->size; i++) {
		// 	if(q->proc[i]->priority< priority) {
		// 		priority = q->proc[i]->priority;
		// 		index_pri = i;
		// 	}
		// }

		struct pcb_t *re_elem = (struct pcb_t *) malloc(sizeof(struct pcb_t));
		re_elem = q->proc[0];

		for (int i = 0; i<q->size; i++) {
			q->proc[i] = q->proc[i+1];
		}

		q->size --;
		return re_elem;
	}

	return NULL;
}

