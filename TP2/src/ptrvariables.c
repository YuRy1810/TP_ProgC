#include <stdint.h>
#include <stdio.h>

int main(void)
{
    char c = 'A';
    short s = -100;
    int i = -1000;
    long int l = -10000L;
    long long int ll = -100000LL;
    float f = 1.5f;
    double d = 3.14159;
    long double ld = 2.71828L;
    char *pc = &c;
    short *ps = &s;
    int *pi = &i;
    long int *pl = &l;
    long long int *pll = &ll;
    float *pf = &f;
    double *pd = &d;
    long double *pld = &ld;

    printf("Avant la manipulation :\n");
    printf("c : %p = %02x\n", (void *)pc, (unsigned char)c);
    printf("s : %p = %04hx\n", (void *)ps, (unsigned short)s);
    printf("i : %p = %08x\n", (void *)pi, (unsigned int)i);
    printf("l : %p = %lx\n", (void *)pl, (unsigned long)l);
    printf("ll: %p = %llx\n", (void *)pll, (unsigned long long)ll);
    printf("f : %p = %a\n", (void *)pf, (double)f);
    printf("d : %p = %a\n", (void *)pd, d);
    printf("ld: %p = %La\n", (void *)pld, ld);

    *pc = 'B';
    *ps = 100;
    *pi = 1000;
    *pl = 10000L;
    *pll = 100000LL;
    *pf = 1.0f;
    *pd = 2.0;
    *pld = 3.0L;

    printf("Apres la manipulation :\n");
    printf("c : %p = %02x\n", (void *)pc, (unsigned char)c);
    printf("s : %p = %04hx\n", (void *)ps, (unsigned short)s);
    printf("i : %p = %08x\n", (void *)pi, (unsigned int)i);
    printf("l : %p = %lx\n", (void *)pl, (unsigned long)l);
    printf("ll: %p = %llx\n", (void *)pll, (unsigned long long)ll);
    printf("f : %p = %a\n", (void *)pf, (double)f);
    printf("d : %p = %a\n", (void *)pd, d);
    printf("ld: %p = %La\n", (void *)pld, ld);
    return 0;
}