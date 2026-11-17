/*
 * router_bitwise.c - the bitwise operations inside a router's lookup.
 *
 */
#include <stdio.h>
#include <stdint.h>

/* <<  and  |  : pack four bytes into one 32-bit address */
uint32_t make_ip(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    return (a << 24) | (b << 16) | (c << 8) | d;
}

/* <<  : build a mask of `prefix` leading 1s */
uint32_t make_mask(int prefix)
{
    if (prefix == 0) {
        return 0;          /* special case: shifting by 32 is undefined in C */
    }
    return 0xFFFFFFFFu << (32 - prefix);
}

/* >>  and  &  : pull each byte back out for printing */
void print_ip(uint32_t ip)
{
    printf("%u.%u.%u.%u", ip >> 24, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

struct route { uint32_t network; int prefix; const char *where; };

int main(int argc, char *argv[])
{
    struct route table[] = {               /* home router table */
        { make_ip(0, 0, 0, 0),       0, "internet via ISP" },
        { make_ip(192, 168, 1, 0),  24, "main LAN"         },
        { make_ip(192, 168, 2, 0),  24, "guest Wi-Fi"      },
        { make_ip(192, 168, 10, 0), 24, "smart home"       },
    };
    int n = sizeof table / sizeof table[0];

    unsigned a, b, c, d;
    if (argc != 2 || sscanf(argv[1], "%u.%u.%u.%u", &a, &b, &c, &d) != 4
        || a > 255 || b > 255 || c > 255 || d > 255) {
        printf("Usage: %s <ip>   e.g. %s 192.168.1.42\n", argv[0], argv[0]);
        return 1;
    }
    uint32_t dest = make_ip(a, b, c, d);

    int best = -1;
    for (int i = 0; i < n; i++) {
        uint32_t mask = make_mask(table[i].prefix);

        /* &  : the core test. Keep the network bits, compare to the route. */
        int match = (dest & mask) == table[i].network;

        printf("dest & ");  print_ip(mask);
        printf(" = ");      print_ip(dest & mask);
        printf("  vs /%-2d %-12s", table[i].prefix, table[i].where);
        if (match) {
            printf(" MATCH");
        }
        printf("\n");

        if (match && (best < 0 || table[i].prefix > table[best].prefix))
            best = i;                       /* longest prefix wins */
    }

    uint32_t mask = make_mask(table[best].prefix);
    printf("\nSend to: %s\n", table[best].where);
    printf("  network part (dest &  mask): "); print_ip(dest & mask);  printf("\n");
    printf("  host part    (dest & ~mask): "); print_ip(dest & ~mask); printf("\n");
    return 0;
}
