#include "engine.h"

void Engine::register_command(std::string name, Wrapper* wrapper) {
  commands.insert({ name, wrapper });
}

int Engine::execute(std::string name, const std::unordered_map<std::string, int>& args) {
  auto command = commands.find(name);
  if (command == commands.end()) {
    std::string errMsg = "Command " + name + " not found";
    throw std::exception(errMsg.c_str());
  }
  return command->second->execute(args);
}
