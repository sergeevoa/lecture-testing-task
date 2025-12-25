#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.h"

#define DEFAULT_ITERS 1000000
#define DEFAULT_RUNS  3

static double seconds_now(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}

void benchmark_push(long iters, int runs)
{
    printf("Benchmark PUSH (%ld ops, %d runs)\n", iters, runs);

    double total_ops = 0.0;

    for (int r = 1; r <= runs; ++r)
    {
        Stack s;
        initStack(&s);

        double start = seconds_now();
        for (long i = 0; i < iters; ++i)
        {
            push(&s, (int)i);
        }
        double elapsed = seconds_now() - start;

        destroyStack(&s);

        double ops = iters / elapsed;
        total_ops += ops;

        printf(" Run %d: time = %.6f s, ops/sec = %.0f\n", r, elapsed, ops);
    }

    printf(" Average ops/sec: %.0f\n\n", total_ops / runs);
}

void benchmark_pop(long iters, int runs)
{
    printf("Benchmark POP (%ld ops, %d runs)\n", iters, runs);

    double total_ops = 0.0;

    for (int r = 1; r <= runs; ++r)
    {
        Stack s;
        initStack(&s);

        for (long i = 0; i < iters; ++i)
        {
            push(&s, (int)i);
        }

        double start = seconds_now();
        for (long i = 0; i < iters; ++i)
        {
            pop(&s);
        }
        double elapsed = seconds_now() - start;

        destroyStack(&s);

        double ops = iters / elapsed;
        total_ops += ops;

        printf(" Run %d: time = %.6f s, ops/sec = %.0f\n", r, elapsed, ops);
    }

    printf(" Average ops/sec: %.0f\n\n", total_ops / runs);
}

int main(int argc, char** argv)
{
    long iters = DEFAULT_ITERS;
    int runs = DEFAULT_RUNS;

    if (argc >= 2) iters = atol(argv[1]);
    if (argc >= 3) runs = atoi(argv[2]);

    printf("Stack benchmark\n");
    printf("Iterations: %ld\nRuns: %d\n\n", iters, runs);

    benchmark_push(iters, runs);
    benchmark_pop(iters, runs);

    return 0;
}
