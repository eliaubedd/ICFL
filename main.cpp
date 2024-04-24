#include "func.hpp"

std::list<std::string> build_ICFL(void){
  std::list<std::string> icfl_text;
  icfl_text.push_back("aaa");
  icfl_text.push_back("baa");
  icfl_text.push_back("caabca");
  icfl_text.push_back("dcaabca");
  return icfl_text;
}

void print_list(std::list<std::string> &list){
  for (std::string& x : list) {
        std::cout << x << " ";
  }
}

void print_bv(pasta::BitVector &bv){
  for (auto it = bv.begin(); it != bv.end(); ++it){
    std::cout << ((*it == true) ? '1' : '0');
  }
  std::cout << std::endl;
}

int getInsertionTarget(pasta::BitVector& b_x, pasta::BitVector& b_z, const std::list<std::string> icfl_t){
  int i = 0, k = 0, u = 0, p = 0, s = 0, q = 0;
  int y = 3;
  std::string alpha = "";

  pasta::FlatRankSelect rs_x(b_x);
  pasta::FlatRankSelect rs_z(b_z);
  
  i = rs_x.select1(1);
  k = b_x.size();
  s = b_x[k] + 1;
  //calcolo upperbound
  if(i < k){
    u = rs_z.rank1(i-1) + b_x[k] + 1;
  }
  else{
    u = rs_z.rank1(b_z.size()) + 1; 
  }

  p = u - 1;

  //TODO
  /*
  while(p >= s){
    q = rs_x.select1(p - b_x[k]);

    for(int c = 0; c < icfl_t.size(); c++){

    }
  }
  */
  


}

int main()
{
      // Create a bit vector of size 1000 containing only zeros and flip every other bit.
  pasta::BitVector bv_x(4, 1);
  pasta::BitVector bv_z(4,0);
  bv_z[0] = 1; 
  bv_z[1] = 1;
  print_bv(bv_x);
  print_bv(bv_z);


  /*
    // Create rank and select support and print the result of some queries.
  pasta::FlatRankSelect rs(bv);
  std::cout << rs.rank0(250) << ", " << rs.rank1(250)
            << ", "
            << rs.select0(250) << ", " << rs.rank1(250)
            << std::endl;
  */

  std::list<std::string> icfl_text = build_ICFL();
  print_list(icfl_text);
  std::string x = "a";
  std::string z = "abca";
  std::cout << getInsertionTarget(bv_x, bv_x, icfl_text);

  return 0;

}