/**
 * @file
 * @brief Wrapper class header file
 * @authors Pavlov Ilya
 *
 * Contains Wrapper and helper classes definitions
 */

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>

/**
 * Needed in order not to make the main Wrapper class template
 */
class WrapperBase {
public:
  virtual int execute(const std::vector<int>&) = 0;
};

/**
 * Needs to save object of class and method 
 */
template <class Class, class... Args>
class WrapperTemp : public WrapperBase {
  friend class Wrapper;
private:
  Class* obj; ///< object of class
  int (Class::* method)(Args...); ///< method

  /**
   * Helps to call method with arguments in vector 
   */
  template <size_t... I>
  int callHelper(const std::vector<int>& args, std::index_sequence<I...>) {
    return (obj->*method)(args[I]...);
  }

  WrapperTemp(Class* obj, int (Class::* method)(Args...)) : obj(obj), method(method) {}

  int execute(const std::vector<int>& args) override {
    return callHelper(args, std::make_index_sequence<sizeof...(Args)>{});
  } 
};

/**
 * Wrapper class for classes' methods 
 */
class Wrapper {
private:
  std::unique_ptr<WrapperBase> pImpl;
  std::vector<std::string> argsOrder;
  std::unordered_map<std::string, int> defaultVals;

public:
  /**
   * Construct wrap for method
   * @param[in] obj pointer to class instance
   * @param[in] method pointer to class method
   * @param[in] args map with default values of args
   */
  template<class Class, class... Args>
  Wrapper(Class* obj, int (Class::* method)(Args...), const std::vector<std::pair<std::string, int>>& args)
  : pImpl(new WrapperTemp<Class, Args... >(obj, method)) {

    argsOrder.reserve(args.size());
    defaultVals.reserve(args.size());
    for (auto& arg : args) {
      argsOrder.push_back(arg.first);
      defaultVals.insert(arg);
    }
  }

  /**
   * Call method with selected arguments
   * @param[in] args map with argumetns and their names
   * @return the result of method
   */
  int execute(const std::unordered_map<std::string, int>& args) {
    std::vector<int> final_args;
    for (auto& arg_name : argsOrder) {
      auto i = args.find(arg_name);
      final_args.push_back(i != args.end() ? i->second : defaultVals.find(arg_name)->second);
    }
    return pImpl->execute(final_args);
  }
};