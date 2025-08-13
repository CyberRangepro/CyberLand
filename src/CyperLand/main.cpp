// server.cpp
#include <iostream>
#include <set>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
#include <xmlrpc-c/server_abyss.hpp>
#include "CyberLand.hpp"
class RequestManagerVirtualMachine : public xmlrpc_c::method {
private:
  /* data */
public:
  RequestManagerVirtualMachine(/* args */);
  ~RequestManagerVirtualMachine();
};

class VirtualMachineclone : public RequestManagerVirtualMachine {
private:
  /* data */
public:
  VirtualMachineclone(/* args */);

  void execute(xmlrpc_c::paramList const &paramList, xmlrpc_c::value *const retvalP) override {
    // Implementation of the clone operation
    // paramList contains the parameters passed to the XML-RPC call
    // retvalP is where you store the return value

    // Example: Get parameters
    int vm_id = paramList.getInt(0);               // First parameter
    std::string new_name = paramList.getString(1); // Second parameter

    // Perform clone operation here...

    // Set return value
    *retvalP = xmlrpc_c::value_int(1); // Return 1 for success
  }

protected:
  void request_execute(xmlrpc_c::paramList const &_paramList) { // xmlrpc_c::methodPtr const
  }
};

class RequestManager {
private:
  struct CyperRegistry {
    std::set<std::string> registered_methods;
    xmlrpc_c::registry registry;
    void addMethod(const std::string &name, const xmlrpc_c::methodPtr &methodP) {
      registered_methods.insert(name);
      registry.addMethod(name, methodP);
    };
    bool exist(const std::string &call) { return registered_methods.find(call) != registered_methods.end(); }
  };
  CyperRegistry RequestManagerRegistry;

public:
  RequestManager(/* args */);
  ~RequestManager();
  void register_xml_methods() {
    xmlrpc_c::methodPtr vm_clone(new VirtualMachineclone());
    RequestManagerRegistry.addMethod("vm.clone", vm_clone);
  }
};

// خلق method 'add' التي تقبل (int a, int b) وترجع a + b
class AddMethod : public xmlrpc_c::method {
public:
  AddMethod() {
    this->_signature = "i:ii"; // return int : two ints
    this->_help = "Add two integers (a, b)";
  }

  void execute(xmlrpc_c::paramList const &params, xmlrpc_c::value *const retval) {
    int a = params.getInt(0);
    int b = params.getInt(1);
    params.verifyEnd(2);
    *retval = xmlrpc_c::value_int(a + b);
  }
};

int main(int argc, char **argv) {
  try {
    xmlrpc_c::registry myRegistry;

    xmlrpc_c::methodPtr const addP(new AddMethod());
    myRegistry.addMethod("math.add", addP);

    // تشغيل خادم Abyss على المنفذ 8080
    xmlrpc_c::serverAbyss server(xmlrpc_c::serverAbyss::constrOpt().registryP(&myRegistry).portNumber(8080));

    std::cout << "C++ XML-RPC server running on port 8080...\n";
    server.run(); // كتلة إلى أن يتوقف الخادم
                  // server.run() لا يرجع عادةً إلا إذا حصل خطأ أو توقف يدوي
  } catch(std::exception const &e) {
    std::cerr << "FATAL: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
