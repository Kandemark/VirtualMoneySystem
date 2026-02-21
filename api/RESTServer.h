#ifndef REST_SERVER_H
#define REST_SERVER_H

// Fully independent - no Crow dependency
#include <functional>
#include <string>


class WalletEndpoints; // Forward declaration

class RESTServer {
public:
  RESTServer(WalletEndpoints &endpoints);
  ~RESTServer();

  void run(int port);
  void stop();

private:
  WalletEndpoints &walletEndpoints;
  bool running;
  int serverPort;
};

#endif // REST_SERVER_H
