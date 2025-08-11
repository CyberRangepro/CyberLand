#pragma once

#include <ostream>
#include <xmlrpc-c/base.hpp>
#include <xmlrpc-c/registry.hpp>
// class ParamList {
// public:
//   ParamList(const xmlrpc_c::paramList *paramList, const std::set<int> &hidden)
//       : _paramList(paramList), _hidden(hidden){};

//   std::string &to_string(std::string &str) const {
//     std::ostringstream oss;

//     oss << get_value_as_string(0);

//     for(unsigned int i = 1; i < _paramList->size(); i++) {
//       oss << " " << get_value_as_string(i);
//     }

//     str = oss.str();

//     return str;
//   };

//   std::string get_value_as_string(int index) const {
//     if(index == 0 || _hidden.count(index) == 1) {
//       return "****";
//     }

//     std::ostringstream oss;
//     xmlrpc_c::value::type_t type((*_paramList)[index].type());

//     if(type == xmlrpc_c::value::TYPE_INT) {
//       oss << _paramList->getInt(index);
//       return oss.str();
//     } else if(type == xmlrpc_c::value::TYPE_I8) {
//       oss << _paramList->getI8(index);
//       return oss.str();
//     } else if(type == xmlrpc_c::value::TYPE_BOOLEAN) {
//       oss << _paramList->getBoolean(index);
//       return oss.str();
//     } else if(type == xmlrpc_c::value::TYPE_STRING) {
//       oss << _paramList->getString(index);
//       return oss.str();
//     } else if(type == xmlrpc_c::value::TYPE_DOUBLE) {
//       oss << _paramList->getDouble(index);
//       return oss.str();
//     }

//     return oss.str();
//   };

//   int size() const { return _paramList->size(); };

// private:
//   const xmlrpc_c::paramList *_paramList;

//   const std::set<int> &_hidden;
// };
class Request : public xmlrpc_c::method2 {
private:
  /* data */
public:
  Request(/* args */);
  ~Request();
};
