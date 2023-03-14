#include <iostream>

import Bitwise;

int main()
{
    const uint32_t a { 0b10101010 };
    std::cout << GetBit(a, 2) << std::endl; // 0b1
    std::cout << GetRangeBit(a, 6, 4) << std::endl; // 0b101
    return 0;
}
