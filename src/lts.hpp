#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>


template <typename State>
class TransFunction {
  using trans_list = std::vector<std::tuple<State, char, State>>;
  using trans_table = std::unordered_map<State, std::unordered_map<char, State>>;
public:
  trans_list t_list;
  TransFunction(trans_list tl) {
    t_list = tl;
    t_table = convert2table(t_list);
  }

  void print() {
    for(auto &t: t_list) {
      auto &s  = std::get<0>(t);
      auto &a  = std::get<1>(t);
      auto &s_ = std::get<2>(t);
      std::cout << s << " --"<< a << "--> " << s_ <<'\n';
    }
  }
  void printt() {
    for (auto it = t_table.begin(); it != t_table.end(); ++it){
        std::cout << it->first << '\n';
        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
          std::cout << "  " << jt->first << " --> " << jt->second << '\n';
    }
  }
private:
  trans_table t_table;
  trans_table convert2table(const trans_list& tl) {
    // ラベルの遷移先を示す型
    using trans_to = std::unordered_map<char, State>;
    trans_table tt;
    for(auto &t: t_list) {
      auto &s  = std::get<0>(t);
      auto &a  = std::get<1>(t);
      auto &s_ = std::get<2>(t);
      // 遷移表にsの状態が登録されているか否か
      tt.try_emplace(s,trans_to());
      tt[s].try_emplace(a,s_);
    }
    return tt;
  }
};
