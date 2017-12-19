#include <stdio.h>
#include <stdlib.h>

#include "state_machine.h"

int callback(void *ctx, int cur_state, int event, int next_state);

event_table events[] = {
	{ 1, 1, 2, &callback },
	{ 1, 2, 3, &callback },
	{ 1, 3, 1, NULL },
	{ 2, 4, 1, &callback },
	{ 3, 5, 2, &callback },
	{ 3, 6, 4, &callback },
	{ 4, 7, 1, NULL },
	{ EOET, EOET, EOET, NULL }
};

int callback(void *ctx, int cur_state, int event, int next_state) {
	printf("callback current = %d, event = %d, next_state = %d\n", cur_state, event, next_state);
	return 1;
}

int main(void) {
	state_machine m;
	int j;
	
	init(&m, 1, events, NULL);
	
	while (1) {
		scanf("%d", &j);
		if (!run(&m, j))
			printf("unhandled event %d\n", j);
	}
	
	return 1;
}

