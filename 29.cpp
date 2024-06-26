#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define STATE_SIZE 25  
#define LANE_SIZE 8    

typedef struct {
    uint64_t lanes[STATE_SIZE];  
} State;

void initialize_state(State *state) {
    memset(state->lanes, 0, STATE_SIZE * sizeof(uint64_t));
}

void absorb(State *state, const uint8_t *block) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state->lanes[i] ^= ((uint64_t *)block)[i];
    }
}

int all_lanes_nonzero(const State *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        if (state->lanes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void print_state(const State *state) {
    for (int i = 0; i < STATE_SIZE; i++) {
        printf("Lane %d: 0x%016lx\n", i, state->lanes[i]);
    }
}

int main() {
    State state;
    uint8_t block[STATE_SIZE * LANE_SIZE] = {0};  

    for (int i = 0; i < STATE_SIZE; i++) {
        block[i * LANE_SIZE] = (i + 1); 
    }

    initialize_state(&state);

    printf("Initial state:\n");
    print_state(&state);

    absorb(&state, block);

    printf("\nState after absorbing P0:\n");
    print_state(&state);

    int rounds = 1;  
    while (!all_lanes_nonzero(&state)) {
        absorb(&state, block);
        rounds++;
    }

    printf("\nTotal rounds to make all lanes non-zero: %d\n", rounds);
    printf("Final state:\n");
    print_state(&state);

    return 0;
}
