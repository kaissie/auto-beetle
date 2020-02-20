#ifndef   BISIM_HPP
#define   BISIM_HPP

#include <iostream>
#include <set>
#include <vector>
#include <utility>
#include "lts.hpp"

template <typename State>
struct Partition {
public:
  using block = std::set<State>;
  using partition = std::set<block>;

  Partition(block states) {
    block_set = {states};
  }
  Partition(partition blocks) {
    block_set = blocks;
  }
  const partition& getBlockSet() const { return block_set; }

  static void refinement(LTS<State> L1, LTS<State> L2) {
    auto state_set = L1.getStateSet();
    auto states_2 = L2.getStateSet();
    auto action_set = L1.getLabelSet();
    auto actions_2 = L2.getLabelSet();
    auto transitions_set = L1.getTransitions();
    auto transitions_2 = L2.getTransitions();

    state_set.insert(states_2.begin(), states_2.end());
    action_set.insert(actions_2.begin(), actions_2.end());
    transitions_set.insert(transitions_2.begin(), transitions_2.end());

    Partition<State> P(state_set);
    std::cout << "Log : "<< P << '\n';
    bool changed = true;
    int i = 1;
    while (changed){
      std::cout << "Step " << i << '\n';
      changed = false;
      for(auto &block: P.block_set) {
        for(auto &action: action_set) {
          //auto sorted_block = sortTransitions(action, block);
          if(changed) break;
          auto splitting = split(block, action, P, transitions_set);
          if (splitting != Partition(block)) {
            P = (P - Partition(block)) + splitting;
            std::cout << "Log : "<< P << '\n';
            changed = true;
            break;
          }
        }
      }
      i++;
    }
  }

  Partition<State> operator+(const Partition<State>& rhs) {
    partition new_part = block_set;
    const partition& add_part = rhs.getBlockSet();
    new_part.insert(add_part.begin(),add_part.end());
    Partition<State> p(new_part);
		return p;
	}
  Partition<State> operator-(const Partition<State>& rhs) {
    partition new_part = block_set;
    const partition& remove_part = rhs.getBlockSet();
    for(auto b: remove_part) {
      new_part.erase(b);
    }
    Partition<State> p(new_part);
    return p;
  }

  inline bool operator==(const Partition<State>& rhs) const {
    return block_set == rhs.getBlockSet();
  }

  inline bool operator!=(const Partition<State>& rhs) const {
    return !(*this == rhs);
  }
  static Partition<State> flatten(const Partition<State>& p) {
    block new_block;
    for(auto block : p.getBlockSet())
      for(auto s : block)
        new_block.insert(s);
    Partition<State> n(new_block);
    return n;
  }

private:
  partition block_set;
  void sortTransitions(char a, block &b) {

  }
  static partition belongBlock(State s, char a, partition p, LTS<State>::trans_table TT) {
    auto ret = TT[s].equal_range(a);
    partition belong_block_set = {};
    for (auto it = ret.first; it != ret.second; ++it){
      for (auto block : p) {
        if(block.contains(it->second)) belong_block_set.insert(block);
      }
    }
    return belong_block_set;
  }
  static Partition<State> split(block B, char a, Partition<State> P, LTS<State>::trans_table TT) {
    State s = *(B.begin());
    State next_s = TT[s].find(a)->second;
    block next_block;
    for (auto p : P.getBlockSet()) {
      if(p.contains(next_s)) next_block = p;
    }
    if (next_block.empty()) next_block = B;
    block b1 = {}, b2 = {};

    for(auto t : B) {
      if(belongBlock(s,a,P.getBlockSet(),TT) == belongBlock(t,a,P.getBlockSet(),TT)) {
        b1.insert(t);
      }else{
        b2.insert(t);
      }
    }

    if (b2.empty()){
      Partition<State> r1(b1);
      return r1;
    }
    else if (b1.empty()){
      Partition<State> r1(b2);
      return r1;
    }else{
      Partition<State> r1(b1);
      Partition<State> r2(b2);
      return r1+r2;
    }
  }
};

template <typename State>
std::ostream& operator<<(std::ostream& os, const Partition<State>& rhs)
{
  os << '[' <<rhs.getBlockSet().size() << ']';
  for(auto block: rhs.getBlockSet()) {
    os << '/';
    for(auto state: block) os << state << ' ';
  }
  os << '/' << '\n';
  return os;
}

template <typename State>
void printPartition(Partition<State> p) {
  for(auto &b: p.getBlockSet()) {
    std::cout << "Partition 1" << '\n';
    for(auto &a: b) {
      std::cout << a << ' ';
    }
    std::cout << '\n';
  }
}


#endif //BISIM_HPP
