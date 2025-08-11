#pragma once
#include "VirtualMachineDefinitions.hpp"
class device {
private:
  VMstruct stanse;

public:
  device(VMstruct &stanse);
  void startVM();
  void shutdown();
  std::string vmStateToString();

  VMstruct getStanse();
};
