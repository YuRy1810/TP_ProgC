#include <stdint.h>
#include <stdio.h>

int main(void)
{
    const uint32_t d = 0x10001000U;
    const uint32_t masque_bit_gauche_4 = UINT32_C(1) << 28;
    const uint32_t masque_bit_gauche_20 = UINT32_C(1) << 12;
    const int resultat = ((d & masque_bit_gauche_4) != 0U)
                      && ((d & masque_bit_gauche_20) != 0U);

    printf("%d\n", resultat);
    return 0;
}