#include <stdio.h>
#include <stdlib.h>

typedef struct RandomGenerator RandomGenerator;
typedef struct RandomOperations RandomOperations;


struct RandomOperations
{
    void
    (*destroy)(struct RandomGenerator *);

    int
    (*next)(struct RandomGenerator *);
};

struct RandomGenerator
{
    struct RandomOperations *ops;
    long long seed, mul, inc, mod;
};

int
next(struct RandomGenerator *rg)
{
    return (int) (rg->seed = (rg->seed * rg->mul + rg->inc) % rg->mod);
}

void
destroy(struct RandomGenerator *rg)
{
    free(rg->ops);
    free(rg);
}


struct RandomGenerator *
random_create(long long seed)
{
    struct RandomGenerator *rg = calloc(1, sizeof(struct RandomGenerator));
    rg->inc = 12345;
    rg->mul = 1103515245;
    rg->mod = (1u << 31);
    rg->seed = seed;
    rg->ops = calloc(1, sizeof(struct RandomOperations));
    rg->ops->next = next;
    rg->ops->destroy = destroy;
    return rg;
}

