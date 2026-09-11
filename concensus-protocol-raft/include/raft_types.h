#pragma once

#include <chrono>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <vector>

namespace raft {

using NodeId = int;
using Term = std::uint64_t;

using LogIndex = std::uint64_t;

struct LogEntry {
    Term term =0;
    std::string command;
};

enum class Role { Follower, Candidate, Leader };

inline const char* roleToString(Role r) {
    switch(r) {
        case Role::Follower: return "Follower";
        case Role::Candidate: return "Candidate";
        case Role::Leader: return "Leader";
    }
    return "?";
}

struct PeerInfo {
    NodeId id;
    std::string host;
    int port;
};

struct Config {
    std::chrono::milliseconds electionTimeoutMin{1000};
    std::chrono::milliseconds electionTimeoutMax{2000};
    std::chrono::milliseconds heartbeatInterval{300};
    std::chrono::milliseconds rpcTimeout{500};
    std::chrono::milliseconds clientWaitTimeout{5000};
    std::string partitionFile;
};

//process wide static mutex to avoid interleaving in mutlithreaded setup
inline std::mutex& logMutex() {
    static std::mutex m;
    return m;
}

inline std::string nowString() {
    //TODO;
    using namespace std::chrono;
    auto now = system_clock::now();
    auto ms = duration_cast<milliseconds>(now.time_since_epoch())%1000;
    auto t = system_clock::to_time_t(now);
    std::tm tmv{};
    //TODO
    localtime_r(&t, &tmv);
    char buf[32];
    std::snprintf(buf, sizeof(buf), "%02d:%02d:%02d.%03d", tmv.tm_hour, tmv.tm_min, tmv.tm_sec, (int)ms.count());
    return buf;
}

inline void logLine(NodeId id, const std::string& msg) {
    std::lock_guard<std::mutex> lk(logMutex());
    std::cout << nowString() << " [node " << id << "] " << msg << std::endl;
}

}