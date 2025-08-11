#pragma once
#include "VMController.hpp"
#include "device.hpp"
#include <string>

class CLI {
public:
  CLI(VirtualMachineManager &vmManager, device &dev);

  bool processCommand();
  void showHelp() const;

private:
  VirtualMachineManager &vmManager;
  device &deV;
  vmType fromStringtoenum(std::string);
  void handleCreateCommand(const std::vector<std::string> &args);
  void handleStartCommand(const std::vector<std::string> &args);
  void handleStopCommand(const std::vector<std::string> &args);
  void handleSleepCommand(const std::vector<std::string> &args);
  void handleWakeCommand(const std::vector<std::string> &args);
  void handleStatusCommand() const;
  void handleListCommand() const;

  std::vector<std::string> tokenize(const std::string &input) const;
};