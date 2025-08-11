#pragma once
#include <libvirt/libvirt.h>
#include <string>
#include <vector>
enum class vmType { PC, ROUTER, SWITCH };
enum class vmStatus { PAUSED, RUNNING, STOPPED, SLEEP };
struct tabInterFaceStruct {
  std::string tabInterFaceName;
  std::string MAC;
  tabInterFaceStruct(const std::string &name, const std::string &mac) : tabInterFaceName(name), MAC(mac) {}
  tabInterFaceStruct() = default;
};

struct VMstruct {
  std::string name;
  std::string ipAddress;
  std::vector<tabInterFaceStruct> tabInterFaceName;
  std::vector<std::string> bridgeName;
  virDomainPtr cloned = nullptr;
  vmStatus status;
  bool active;
  time_t lastActivityTime;
};