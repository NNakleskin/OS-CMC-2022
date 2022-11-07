#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/* 
seed - начальное значение
1103515245 - множитель
инкремент - 12345
2^31 - модуль
*/

enum Constants {
    MULTIP = 1103515245,
    INCR = 12345,
    MOD = pow(2, 31)
};


void destroy(RandomGenerator *rr) {
    free(rr);
}


int next(RandomGenerator *rr) {
    int tmp = (MULTIP * rr->seed + INCR) % MOD;
    rr->seed = tmp;
    return tmp;
}


typedef struct RandomGenerator
{
    int seed;
    void (*destroy) (RandomGenerator *rr);
    int (*next) (RandomGenerator *rr);
} RandomGenerator;


RandomGenerator *random_create(int seed) {
    RandomGenerator *rr = calloc(1, sizeof(RandomGenerator));
    rr->seed = seed;
    return rr;
}


int main(void) {
    RandomGenerator *rr = random_create(1234);
    for (int j = 0; j < 100; ++j) {
        printf("%d\n", rr->ops->next(rr));
    }
    rr->ops->destroy(rr);
    return 0;
} 
