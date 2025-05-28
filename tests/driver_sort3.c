#include "push_swap.h"
int main(void) {
    t_stack_node *a = NULL;
    char *nums[] = {"1 2 3", NULL};
    init_stack(&a, nums);
    sort_three(&a);
    // dump
    while (a) {
        ft_putnbr_fd(a->value, 1);
        if (a->next) write(1, " ", 1);
        a = a->next;
    }
    write(1, "\n", 1);
    free_stack(&a);
    return 0;
}
