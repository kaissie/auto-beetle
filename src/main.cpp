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
  std::cout << "==================================" << '\n';
  LTS<int> lts1({ {0,'a',1},{0,'a',2},{1,'b',2},{2,'b',2} });
  LTS<int> lts2({ {10,'a',11},{11,'b',11} });
  lts1.printAll();
  lts2.printAll();
  std::cout << "Rifinemented Partition" << '\n';
  std::cout << Partition<int>::refinement(lts1,lts2) << '\n';
  std::cout << "==================================" << '\n';
  LTS<std::string> lts3({
    {"s0",'a',"s1"},{"s0",'a',"s2"},
    {"s1",'a',"s3"},{"s1",'b',"s4"},
    {"s2",'a',"s4"},
    {"s3",'a',"s0"},
    {"s4",'a',"s0"}});
  LTS<std::string> lts4({
    {"t0",'a',"t1"},{"t0",'a',"t3"},
    {"t1",'a',"t2"},{"t1",'b',"t2"},{"t1",'b',"t5"},
    {"t2",'a',"t0"},
    {"t3",'a',"t4"},
    {"t4",'a',"t0"},
    {"t5",'a',"t0"},
    {"t5",'a',"t4"}});
  lts3.printAll();
  lts4.printAll();
  std::cout << "Rifinemented Partition" << '\n';
  std::cout << Partition<std::string>::refinement(lts3,lts4) << '\n';
}

int main(int argc, char const *argv[]) {
  std::cout << "Hello, auto-beetle!" << '\n';
  //test_lts();
  //test_dfa();
  test_bisim();
}
