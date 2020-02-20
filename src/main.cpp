#include <iostream>
#include <string>
#include "dfa.hpp"
#include "bisim.hpp"

void test_dfa () {
  std::cout << "DFA test function" << '\n';
  std::set<int> accept_s = {0};
  int init_s = 0;
  std::vector<std::tuple<int, char, int>> values = {
    {0,'0',0},{0,'1',1},
    {1,'0',2},{1,'1',0},
    {2,'0',1},{2,'1',2}};
  DFA<int> dfa(values, init_s, accept_s);
  dfa.printAll();
  std::cout << std::boolalpha <<dfa.run("10010") << '\n';
}
void test_lts() {
  std::cout << "LTS test function" << '\n';
  std::vector<std::tuple<int, char, int>> values = { {0,'A',0},{0,'A',1},{0,'B',1},{1,'B',1} };
  LTS<int> lts(values);
  lts.printAll();
}

void test_bisim() {
  Partition<int> p0({1,2,3,4,5});
  Partition<int> p1({6,7,8});
  Partition<int> p2({6,8,7});
  //printPartition(p);
  std::cout << "Partition" << (p0+p1+p2) - p0 << '\n';
  if (p1 == p2) {
    std::cout << Partition<int>::flatten(p0+p2) << '\n';
  }

}

int main(int argc, char const *argv[]) {
  std::cout << "Hello, auto-beetle!" << '\n';
  test_lts();
  test_dfa();
  test_bisim();
}
