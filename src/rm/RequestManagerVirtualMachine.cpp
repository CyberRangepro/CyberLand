#include "RequestManagerVirtualMachine.hpp"


void VirtualMachineClone::execute(xmlrpc_c::paramList const &paramList, xmlrpc_c::value *const retvalP)  {
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