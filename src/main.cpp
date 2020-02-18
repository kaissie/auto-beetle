#include <iostream>
#include <string>
#include "dfa.hpp"
#include "lts.hpp"

void interface(){
  std::set<char> state_set;
  char init_state;
  std::set<char> accept_state_set;
  std::set<char> alphabet_set;
  std::unordered_map<char, std::unordered_map<char, char>> transitions;

  std::cout << "Enter states ( '}' is end )" << '\n';
  char inchar;
  std::cout << "state_set = {" << "\n";
  while(true){
    std::cin >> inchar;
    if (inchar == '}')
      break;
    state_set.insert(inchar);
  }
  for(auto s: state_set)
    std::cout << s << ", ";
  std::cout << '\n';

  std::cout << "Enter the init state ( '}' is end )" << '\n';
  std::cout << "init_state = ";
  std::cin >> init_state;

  std::cout << "Enter accept states ( '}' is end )" << '\n';
  std::cout << "accept_state_set = {" << "\n";
  while(true){
    std::cin >> inchar;
    if (inchar == '}')
      break;
    accept_state_set.insert(inchar);
  }
  std::cout << "Enter alphabet ( '}' is end )" << '\n';
  std::cout << "alphabet_set = {" << "\n";
  while(true){
    std::cin >> inchar;
    if (inchar == '}')
      break;
    alphabet_set.insert(inchar);
  }
  for(auto s: alphabet_set)
    std::cout << s << ", ";
  std::cout << '\n';

  std::cout << "Enter transition table ( '}' is end )" << '\n';
  std::cout << "transitions = {" << "\n";
  for(auto s: state_set) {
    std::unordered_map<char, char> to_state;
    for(auto c: alphabet_set) {
      std::cout << s << " -"<< c << "-> ";
      std::cin >> inchar;
      to_state.emplace(c,inchar);
    }
    transitions.emplace(s,to_state);
  }
  std::cout << "Transition Function" << '\n';
  for(auto s: transitions) {
    for(auto c: transitions.at(s.first)) {
      std::cout << s.first << " -"<< c.first << "-> ";
      std::cout << c.second << '\n';
    }
  }


  DFA<char> dfa{state_set,alphabet_set,init_state,accept_state_set,transitions};
  std::string instr;
  while(true){
    std::cout << ">> ";
    std::cin >> instr;
    if (instr == "exit")
      break;
    std::cout << std::boolalpha <<dfa.run(instr) << '\n';
  }
}

void test_dfa() {
  std::cout << "DFA test function" << '\n';
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
  interface();
}

void test_lts() {
  std::cout << "LTS test function" << '\n';
  std::vector<std::tuple<int, char, int>> values = { {0,'A',0},{0,'A',1},{0,'B',1},{1,'B',1} };
  TransFunction<int> tf(values);
  tf.printAll();
}

int main(int argc, char const *argv[]) {
  std::cout << "Hello, auto-beetle!" << '\n';
  test_lts();
}
