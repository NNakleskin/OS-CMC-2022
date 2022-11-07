#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
seed - начальное значение
1103515245 - множитель
инкремент - 12345
2^31 - модуль
*/


struct RandomGenerator;
struct RandomOperations;
void destroy(struct RandomGenerator *rr);
int next(struct RandomGenerator *rr);


enum Constants {
    MULTIP = 1103515245,
    INCR = 12345,
    MOD = 2147483648
};


typedef struct RandomOperations
{
    void (*destroy)(struct RandomGenerator *rr);
    int (*next)(struct RandomGenerator *rr);
}RandomOperations;


typedef struct RandomGenerator
{
    long long seed;
    RandomOperations *ops;
} RandomGenerator;


void destroy(RandomGenerator *rr) {
    free(rr->ops);
    free(rr);
}


int next(RandomGenerator *rr) {
    long long tmp = (MULTIP * rr->seed + INCR) % MOD;
    rr->seed = (int) tmp;
    return (int) tmp;
}


RandomGenerator *random_create(long long seed) {
    RandomGenerator *rr = calloc(1, sizeof(RandomGenerator));
    rr->seed = seed;
    rr->ops = calloc(1, sizeof(RandomOperations));
    rr->ops->next = next;
    rr->ops->destroy = destroy;
    return rr;
}

/*
int main(void) {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
    return 0;
} */


