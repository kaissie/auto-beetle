#include <iostream>
#include <unordered_map>
#include <map>
#include <tuple>
#include <vector>


template <typename State>
class TransFunction {
  using trans_list = std::vector<std::tuple<State, char, State>>;
  using trans_table = std::unordered_map<State, std::multimap<char, State>>;
public:
  TransFunction(trans_list tl) {
    t_list = tl;
    t_table = convert2table(t_list);
    state_set = getStateSet(t_list);
    label_set = getLabelSet(t_list);
  }

  void print() {
    for(auto &t: t_list) {
      auto &s  = std::get<0>(t);
      auto &a  = std::get<1>(t);
      auto &s_ = std::get<2>(t);
      std::cout << s << " --"<< a << "--> " << s_ <<'\n';
    }
  }

  void printTable() {
    std::cout << "<< Transition Table >>" << '\n';
    for (auto it = t_table.begin(); it != t_table.end(); ++it){
        std::cout << it->first << '\n';
        for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
          std::cout << "  " << jt->first << " --> " << jt->second << '\n';
    }
  }
  void printStates() {
    std::cout << "<< States >>" << '\n';
    for(auto s: state_set)
      std::cout << s <<" ";
    std::cout << '\n';
  }

  void printLabels() {
    std::cout << "<< Labels >>" << '\n';
    for(auto l: label_set)
      std::cout << l <<" ";
    std::cout << '\n';
  }

  void printAll() {
    printStates();
    printLabels();
    printTable();
  }

private:
  trans_list t_list;          // タプル型のリストで表した状態遷移表
  std::set<State> state_set;  // 状態の集合
  std::set<char> label_set;// ラベルの集合
  trans_table t_table;        // 連想配列で表した状態遷移表

  // タプル型リストから連想配列への変換
  trans_table convert2table(const trans_list& tl) {
    using trans_to = std::multimap<char, State>; // ラベルの遷移先を表す型
    trans_table tt;
    for(auto &t: t_list) {
      auto &s  = std::get<0>(t);
      auto &a  = std::get<1>(t);
      auto &s_ = std::get<2>(t);
      // 遷移表にsの状態が登録されているか否か
      tt.try_emplace(s,trans_to());
      tt[s].emplace(a,s_);
    }
    return tt;
  }

  // 遷移リストから状態の集合を取得
  std::set<State> getStateSet(const trans_list& tl){
    std::set<State> set;
    for(auto &t: t_list) {
      auto &state  = std::get<0>(t);
      set.insert(state);
    }
    return set;
  }
  // 遷移リストからラベルの集合を取得
  std::set<char> getLabelSet(const trans_list& tl){
    std::set<char> set;
    for(auto &t: t_list) {
      auto &label  = std::get<1>(t);
      set.insert(label);
    }
    return set;
  }

};
