#pragma once

#include "raft_types.h"

#include <atomic>
#include <optional>
#include <string>
#include <thread>
#include <vector>


namespace raft{
class RpcHandler{
    public:
    virtual ~RpcHandler() = default;

    virtual void onRequestVote(Term term, NodeId candidateId, LogIndex lastLogIndex, 
        Term lastLogTerm, Term& outTerm, bool& outVoteGranted)=0;
    virtual void onAppendEntries(Term term, NodeId leaderId, LogIndex prevLogIndex,
        Term prevLogTerm, const std::vector<LogEntry>& entries, LogIndex leaderCommit,
        Term& outTerm, bool& outSuccess)=0;
    virtual void onClientSet(const std::string& key, const std::string& value,
        std::string& outResponse)=0;
    virtual void onClientGet(const std::string& key, std::string& outResponse)=0;
    virtual void onStatus(std::string& outResponse) =0;

};


struct RequestVoteResult {
    Term term =0;
    bool voteGranted = false;
    bool ok=false;
};

struct AppendEntriesResult{
    Term term=0;
    bool success = false;
    bool ok = false;

};

class Transport {
    public:
    Transport(NodeId selfId, int listenPort, std::vector<PeerInfo> peers,
        std::string partitionFile, int rpcTimeoutMs);
    void start(RpcHandler* handler);
    void stop();

    RequestVoteResult sendRequestVote(NodeId peer, Term term, NodeId candidateId,
        LogIndex lastLogIndex, Term lastLogTerm);
    AppendEntriesResult sendAppendEntries(NodeId peer, Term term, NodeId leaderId,
        LogIndex prevLogIndex, Term prevLogTerm, const std::vector<LogEntry>& entries,
        LogIndex leaderCommit);
    bool isPartitionedFrom(NodeId peer) const;

    private:
    void acceptLoop();
    void handleConnection(int clientFd);
    const PeerInfo* findPeer(NodeId id) const;

    NodeId selfId_;
    int listenPort_;
    std::vector<PeerInfo> peers_;
    std::string partitionFile_;
    int rpcTimeoutMs_;

    RpcHandler* handler_ = nullptr;
    int listenFd_=-1;
    std::atomic<bool> stop_{false};
    std::thread acceptThread_;
    
};

}