#include <stdio.h>
#include <stdlib.h>


int main(void) {
    int first_a, first_b, second_a, second_b;
    scanf("%d%d%d%d", &first_a, &first_b, &second_a, &second_b);

    int res_1 = 0, res_2;
    if(first_a > second_a) {
        res_1 = first_a;
    } else {
        res_1 = second_a;
    }
    if(first_b > second_b) {
        res_2 = second_b;
    } else {
        res_2 = first_b;
    }
    
    


    if(res_1 >= res_2) {
        res_1 = 0;
        res_2 = 0;
    }
    
    printf("%d %d\n",res_1, res_2);

    return 0;
}
