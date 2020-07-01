#ifndef   DFA_HPP
#define   DFA_HPP

#include <set>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>
#include "lts.hpp"

/**
* 文字列をvector<char>に変換する
*/
std::vector<char> str2vec(std::string text){
  auto code = std::vector<char>((int)text.size());
  std::transform(text.begin(), text.end(), code.begin(), [](char x){return x;});
  return code;
}

template <typename State>
class DFA : public LTS<State>{
  State init_state;
  std::set<State> accept_state_set;
public:
  DFA(LTS<State>::trans_list tl, State init_s, std::set<State> accept_s) : LTS<State>(tl) {
    init_state = init_s;
    accept_state_set = accept_s;
  }

  bool run(std::string input_text){
    auto seq = str2vec(input_text);
    int state = init_state;
    for(char c: seq){
      if (this->label_set.contains(c)){
        auto alpha2state_pair = *(this->t_table.at(state).find(c));
        state = alpha2state_pair.second;
      } else
        std::cout << "ERROR : <" << c << "> isn't contained " << '\n';
    }
    return accept_state_set.contains(state);
  }
};

#endif // DFA_HPP
