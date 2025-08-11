#include "Request.hpp"

class RequestManagerVirtualMachine : public Request

{
protected:
  RequestManagerVirtualMachine(const std::string &method_name, const std::string &help, const std::string &params) {}
};

class VirtualMachineClone : public RequestManagerVirtualMachine

{
private:
  /* data */
public:
  VirtualMachineClone(/* args */)
      : RequestManagerVirtualMachine("one.vm.deploy", "Deploys a virtual machine", "A:siibis") {
    
  }
  void execute(xmlrpc_c::paramList const &paramList, xmlrpc_c::value *const retvalP) override ;
  ~VirtualMachineClone();
};
