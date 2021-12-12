/**
 * @file
 * @brief Engine class header file
 * @authors Pavlov Ilya
 *
 * Contains Engine class declarationss
 */

#pragma once

#include "../wrapper/wrapper.hpp"
#include <unordered_map>

/**
 * @brief Engine class
 *
 * Class for managing commands 
 */
class Engine {
private:
  std::unordered_map<std::string, Wrapper*> commands;
public:
  /**
   * Register command to execute it later
   * @param[in] name command name
   * @param[in] wrapper wrapper with class method
   */
  void register_command(std::string name, Wrapper* wrapper);

  /**
   * Execute command with selected name and arguments
   * @param[in] name command name
   * @param[in] args map with argumetns and their names
   * @return the result of command
   */
  int execute(std::string name, const std::unordered_map<std::string, int>& args);
};