#pragma once
#include <csignal>

class SignalHandler {
public:
  static void setupSignalHandlers();
  static void signalHandler(int signal);

private:
  static void cleanupResources();
};