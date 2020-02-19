#ifndef   BISIM_HPP
#define   BISIM_HPP

#include <set>
#include <utility>
#include "lts.hpp"

template <typename State>
struct Partition {
public:
  using block = std::set<State>;
  using partition = std::set<block>;
  partition block_set;
  Partition(block states) {
    block_set = {states};
  }

  void refinement(LTS<State> L1, LTS<State> L2) {
    std::set<State> state_set;
    std::set<char> action_set;
    Partition<State> P(state_set);
    bool changed = true;
    while (changed){
      changed = false;
      for(auto &block: P.block_set) {
        for(auto &action: action_set) {
          sortTransitions(action, block);
          if (split(block,action,P) != Partition(block)) {
            P = (P - Partition(block)) + split(block,action,P);
            changed = true;
            break;
          }
        }
      }
    }
  }


private:
  void sortTransitions(char a, block &b) {

  }
  Partition<State> split(block B, char a, Partition<State> P) {
    return Partition<State>(B);
  }

  Partition<State> operator+(const Partition<State>& rhs) {
		return rhs;
	}
  Partition<State> operator-(const Partition<State>& rhs) {
    return rhs;
  }
  bool operator==(const Partition<State>& rhs) const {
    return rhs;
  }

  inline bool operator!=(const Partition<State>& rhs) const
  {
      return !(*this == rhs);
  }
};


template <typename State>
void printPartition(Partition<State> p) {
  for(auto &b: p.block_set) {
    std::cout << "Partition 1" << '\n';
    for(auto &a: b) {
      std::cout << a << ' ';
    }
    std::cout << '\n';
  }
}


#endif //BISIM_HPP
