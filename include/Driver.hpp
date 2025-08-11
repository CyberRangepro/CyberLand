template <typename MSG> class Driver {
private:
  /* data */
public:
  using message_t = MSG;

  /**
   *  A call to the start() method is needed to start the driver
   *    @param c the command to execute the driver
   *    @param a the arguments for the command
   *    @param ct max number of concurrent threads
   */
  Driver(const std::string &c, const std::string &a, int ct) : cmd(c), arg(a), concurrency(ct) {}
  ~Driver();
};
