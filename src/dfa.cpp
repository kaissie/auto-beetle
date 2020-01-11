#include <set>


struct state {

};

struct alphabet {

};

struct trans_table {

};


class DFA {
  std::set<state> state_set;
  std::set<alphabet> state_set;
  state init_state;
  std::set<state> accept_state_set;
  trans_table transitions;
  bool run()
  {

  }
};
