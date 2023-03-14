module;

#include <cassert>
#include <concepts>

export module Bitwise;

inline constexpr size_t NumBits(size_t numBytes) noexcept
{
    return 8 * numBytes;
}

export bool GetBit(std::integral auto word, size_t nbit)
{
    assert(nbit >= 1 && nbit <= NumBits(sizeof(word)));
    return (word >> (nbit - 1)) & 1;
}

export auto GetRangeBit(std::integral auto word, size_t last, size_t first) -> decltype(word)
{
    assert(last >= 1 && last <= NumBits(sizeof(word)));
    assert(first >= 1 && first <= NumBits(sizeof(word)));
    const auto one = static_cast<decltype(word)>(1);
    const auto mask = (one << (last - first + 1)) - one;
    const auto val = word >> (first - 1);
    return val & mask;
}

export void SetRangeBit(std::integral auto* word, size_t last, size_t first, bool val)
{
    assert(last >= 1 && last <= NumBits(sizeof(word)));
    assert(first >= 1 && first <= NumBits(sizeof(word)));
    const auto one = static_cast<decltype(word)>(1);
    const auto mask = (one << (last - first + 1)) - one;
    if (val)
        *word |= (mask << (first - 1));
    else
        *word &= ~(mask << (first - 1));
}

export void CopyRangeBit(std::integral auto* word, size_t last, size_t first, std::integral auto val)
{
    static_assert(sizeof(*word) >= sizeof(val), "The word should be at least as large as the value");
    assert(last >= 1 && last <= NumBits(sizeof(*word)));
    assert(first >= 1 && first <= NumBits(sizeof(*word)));
    const auto mask = static_cast<decltype(*word)>(val) << (first - 1);
    set_range_bit(word, last, first, 0);
    *word |= mask;
}