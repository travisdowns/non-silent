#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include <err.h>

int cpu_ms() {
    return (int)(clock() * 1000 / CLOCKS_PER_SEC);
}

int main(int argc, char** argv) {

    bool do_stores = false;
    if (argc < 2 || strcmp(argv[1], "-s") == 0) {
        do_stores = true;
        argv++;
        argc--;
    }
    if (argc < 2) errx(EXIT_FAILURE, "provide the array size in KB on the command line");

    size_t size = atol(argv[1]) * 1024;
    unsigned char *p = malloc(size);
    if (!p) errx(EXIT_FAILURE, "malloc of %zu bytes failed", size);

    int fill = argv[2] ? argv[2][0] : 'x'; 
    memset(p, fill, size);

    int startms = cpu_ms();
    printf("allocated %zu bytes at %p and set it to %d in %d ms\n", size, p, fill, startms);

    // wait until 500ms has elapsed from start, so that perf gets the read phase
    while (cpu_ms() - startms < 500) {}
    startms = cpu_ms();

    if (do_stores) {
        for (size_t off = 0; off < 64; off++) {
            for (size_t i = 0; i < size; i += 64) {
                p[i + off] = i;
            }
        }
        int delta = cpu_ms() - startms;
        printf("stores done in %d ms \n", delta);
    } else {
        unsigned char sum = 0;
        for (size_t off = 0; off < 64; off++) {
            for (size_t i = 0; i < size; i += 64) {
                sum += p[i + off];
            }
        }
        int delta = cpu_ms() - startms;
        printf("sum was %u in %d ms \n", sum, delta);
    }

    return EXIT_SUCCESS;
}