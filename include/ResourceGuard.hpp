// ResourceGuard.hpp
#pragma once
#include <filesystem>
#include <functional>
#include <libvirt/libvirt.h>
#include <vector>

class DomainGuard {
private:
  virDomainPtr domain_;

public:
  explicit DomainGuard(virDomainPtr domain) : domain_(domain) {}

  ~DomainGuard() {
    if(domain_) {
      virDomainDestroy(domain_);
      virDomainUndefine(domain_);
      virDomainFree(domain_);
    }
  }

  virDomainPtr get() { return domain_; }
  virDomainPtr release() {
    virDomainPtr temp = domain_;
    domain_ = nullptr;
    return temp;
  }
};

class TapInterfaceGuard {
private:
  std::vector<std::string> interfaces_;

public:
  void addInterface(const std::string &name) { interfaces_.push_back(name); }

  ~TapInterfaceGuard() {
    for(const auto &name : interfaces_) {
      std::string cmd = "sudo ip link delete " + name;
      std::system(cmd.c_str());
    }
  }
};

class DiskGuard {
private:
  std::vector<std::filesystem::path> disks_;

public:
  void addDisk(const std::filesystem::path &path) { disks_.push_back(path); }

  ~DiskGuard() {
    for(const auto &disk : disks_) {
      std::error_code ec;
      std::filesystem::remove(disk, ec);
    }
  }
};