#include <pasta/bit_vector/bit_vector.hpp>
#include <pasta/bit_vector/support/flat_rank_select.hpp>
#include <iostream>
#include <list>

int main()
{
    // Create a bit vector of size 1000 containing only zeros and flip every other bit.
pasta::BitVector bv(1000, 0);
for (size_t i = 0; i < bv.size(); ++i) {
  if (i % 2 == 0) {  bv[i] = 1; }
}
// Print the bit vector to see that everything worked ;-)
for (auto it = bv.begin(); it != bv.end(); ++it) {
  std::cout << ((*it == true) ? '1' : '0');
}
std::cout << std::endl;

// Create rank and select support and print the result of some queries.
pasta::FlatRankSelect rs(bv);
std::cout << rs.rank0(250) << ", " << rs.rank1(250)
          << ", "
          << rs.select0(250) << ", " << rs.rank1(250)
          << std::endl;

    return 0;
}