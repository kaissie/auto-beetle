#include <iostream>
#include <string>
#include "dfa.hpp"

int main(int argc, char const *argv[]) {
  std::cout << "Hello, auto-beetle!" << '\n';
  DFA<int> dfa{
    // 状態の集合
    {0,1,2},
    // アルファベットの集合
    {'0','1'},
    // 初期状態
    0,
    // 受理状態の集合
    {0},
    // 状態遷移表
    {
      {0, {{'0',0}, {'1',1}}},
      {1, {{'0',2}, {'1',0}}},
      {2, {{'0',1}, {'1',2}}}
    }
  };
  std::string instr;
  dfa.print();
  while(true){
    std::cout << ">> ";
    std::cin >> instr;
    if (instr == "exit")
      break;
    std::cout << std::boolalpha <<dfa.run(instr) << '\n';
  }
  std::cout << "s" << '\n';
  return 0;
}
