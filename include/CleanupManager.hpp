#pragma once
#include <functional>
#include <mutex>
#include <vector>

class CleanupManager {
private:
  static std::vector<std::function<void()>> cleanupCallbacks_;
  static std::mutex mutex_;

public:
  static void addCleanupCallback(std::function<void()> callback);
  static void executeCleanup();
  static void setupAtExit();
};