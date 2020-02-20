#ifndef   BISIM_HPP
#define   BISIM_HPP

#include <iostream>
#include <set>
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
  Partition<State> split(block B, char a, Partition<State> P) {
    return Partition<State>(B);
  }

};

template <typename State>
std::ostream& operator<<(std::ostream& os, const Partition<State>& rhs)
{
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
