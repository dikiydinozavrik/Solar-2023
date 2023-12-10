#pragma once
#include <string>

using namespace std;

class ProcessManager {
public:
    ProcessManager(int pid, int port, string maliculous_server);
    void killProcess();
    void sleepProcess();
    void resumeProcess();
    void blockConnection();

private:
    int pid;
    int port;
    string malicious_server;
};
