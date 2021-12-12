/**
 * @file
 * @brief Engine class source file
 * @authors Pavlov Ilya
 *
 * Contains Engine class definition
 */

#include "engine.h"

/**
 * Register command to execute it later
 * @param[in] name command name
 * @param[in] wrapper wrapper with class method
 */
void Engine::register_command(std::string name, Wrapper* wrapper) {
  commands.insert({ name, wrapper });
}

/**
 * Execute command with selected name and arguments
 * @param[in] name command name
 * @param[in] args map with argumetns and their names
 */
int Engine::execute(std::string name, const std::unordered_map<std::string, int>& args) {
  auto command = commands.find(name);
  if (command == commands.end()) {
    std::string errMsg = "Command " + name + " not found";
    throw std::exception(errMsg.c_str());
  }
  return command->second->execute(args);
}
