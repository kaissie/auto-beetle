#ifndef   DFA_HPP
#define   DFA_HPP

#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>

template <typename T>
struct state {
  const T value;
};

struct alphabet {

};
//
// template <typename State>
// struct trans_table {
//   const std::unordered_map<State, std::unordered_map<char, State>> table;
// };

/**
* 文字列をvector<char>に変換する
*/
std::vector<char> str2vec(std::string text){
  auto code = std::vector<char>((int)text.size());
  std::transform(text.begin(), text.end(), code.begin(), [](char x){return x;});
  return code;
}

template <typename State>
class DFA {
  using trans_table = std::unordered_map<State, std::unordered_map<char, State>>;
public:
  std::set<State> state_set;
  std::set<char> alphabet_set;
  State init_state;
  std::set<State> accept_state_set;
  trans_table transitions;
  bool run(std::string input_text){
    auto seq = str2vec(input_text);
    int state = init_state;
    for(char c: seq){
      if (alphabet_set.contains(c))
        state = transitions.at(state).at(c);
      else
        std::cout << "ERROR : <" << c << "> isn't contained " << '\n';
    }
    return accept_state_set.contains(state);
  }
  void print(){
    std::cout << "Hello, dfa" << '\n';
  }

  void print_table();
};

#endif // DFA_HPP
