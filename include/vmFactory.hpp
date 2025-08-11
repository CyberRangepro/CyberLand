#pragma once
#include "ResourceGuard.hpp"
#include "VirtualMachineDefinitions.hpp"
#include "device.hpp"
#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <absl/strings/str_cat.h>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/process.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libvirt/libvirt-domain.h>
#include <libvirt/libvirt.h>
#include <libvirt/virterror.h>
#include <nlohmann/json.hpp>
#include <random>
#include <stdexcept>
#include <tinyxml2.h>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace expr = boost::log::expressions;
namespace bp = boost::process;
namespace fs = std::filesystem;
using json = nlohmann::json;
using absl::Status;
using absl::StatusOr;
using namespace tinyxml2;
#define TEMPPATH "/var/lib/libvirt/temp"
struct VMConfig {
  vmType type;
  fs::path baseDisk;
  fs::path cloneDisk;
  std::string name;
  std::vector<tabInterFaceStruct> tabInterFace;
  virDomainPtr cloned = nullptr;
  vmStatus status;
  std::string vmXML;
  fs::path sharedFolder;
};
class vmFactory {
private:
  virConnectPtr conn = nullptr;
  std::vector<std::unique_ptr<DomainGuard>> domainGuards_;
  std::vector<std::unique_ptr<TapInterfaceGuard>> tapGuards_;
  std::vector<std::unique_ptr<DiskGuard>> diskGuards_;
  void initLogging();
  void createstanseVM(VMConfig &config, VMstruct &stanse);
  bool vmDefineXML(VMConfig &config);
  StatusOr<std::string> buildXML(VMConfig &config);
  StatusOr<void> runCommand(const std::vector<std::string> &args);
  std::string generatMAC();
  bool createTapInterface(std::string &tapName);
  void deleteTapInterfaces(VMConfig &config);
  bool createDisk(VMConfig &config);
  void deleteCloneDisk(VMConfig &config);
  bool setupConfiguration(VMConfig &config);
  int clintesNumber;
  std::unique_ptr<device> createVM(VMConfig &config);

  /*-----------------------------vm MANGE-------------------------------*/
public:
  vmFactory(virConnectPtr conn);
  std::unique_ptr<device> createClinte();
  void registerDomain(virDomainPtr domain);
  void registerTapInterface(const std::string &name);
  void registerDisk(const std::filesystem::path &path);
  void cleanupAll();
};
