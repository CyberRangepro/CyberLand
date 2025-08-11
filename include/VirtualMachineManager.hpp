#pragma once
#include "VirtualMachineDefinitions.hpp"
#include "device.hpp"
#include "vmFactory.hpp"
#include <functional>
#include <memory>
#include <vector>

class VirtualMachineManager {
private:
  virConnectPtr conn = nullptr;
  std::unique_ptr<vmFactory> factory;
  std::vector<std::unique_ptr<device>> runningVM;
  std::map<vmType, std::function<std::unique_ptr<device>()>> creators_;
  void deleteTapInterfaces(VMstruct &stanse);

public:
  VirtualMachineManager();
  std::unique_ptr<device> creatVM(vmType Type);
  void cleanup();

  ~VirtualMachineManager();
};
