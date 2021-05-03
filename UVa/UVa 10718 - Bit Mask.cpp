#include <iostream>

unsigned mostSignificantBit(unsigned number);

int main()
{
    unsigned N, L, U;
    while (scanf("%u %u %u", &N, &L, &U) == 3)
    {
        unsigned M = 0;
        unsigned i_will_be_extracting_most_signicifant_bit_from_this_shit = L; //i really dont know how to name this
        for (int i = 0; i < 32; i++)
        {
            unsigned partial_mask = 1 << (31 - i);
            if ((M | partial_mask) <= U && (N & partial_mask) == 0)
                M |= partial_mask;
            if (mostSignificantBit(i_will_be_extracting_most_signicifant_bit_from_this_shit) == partial_mask && M < L)
            {
                M |= partial_mask;
                i_will_be_extracting_most_signicifant_bit_from_this_shit ^= partial_mask;
            }
        }
        printf("%u\n", M);
    }
    return 0;
}

unsigned mostSignificantBit(unsigned number)
{
    for (int i = 0; i < 32; i++)
    {
        unsigned mask = 1 << (31 - i);
        if (mask & number)
            return mask;
    }
    return 0;
}
