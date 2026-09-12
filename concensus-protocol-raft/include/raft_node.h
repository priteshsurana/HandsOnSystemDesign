#pragma once

#include "kv_store.h"
#include "raft_logic.h"
#include "storage.h"
#include "transport.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <optional>
#include <random>
#include <thread>
#include <unordered_map>

namespace raft{

class RaftNode: public RpcHandler{
    public:
    RaftNode(NodeId id, std::vector<PeerInfo> peers, Storage& storage, KVStore& kv, 
        Transport& transport, Config config);
    void start();
    void stop();

    void onRequestVote(Term term, NodeId candidateId, LogIndex lastLogIndex, Term lastLogTerm,
        Term& outTerm, bool& outVoteGranted) override;
    void onAppendEntries(Term term, NodeId leaderId, LogIndex prevLogIndex, Term prevLogTerm,
        const std::vector<LogEntry>& entries, LogIndex leaderCommit, Term& outTerm, 
        bool& outSuccess) override;
    void onClientSet(const std::string& key, const std::string& value, std::string& outResponse) override;
    void onClientGet(const std::string& key, std::string& outResponse) override;
    void onStatus(std::string& outResponse) override;

    private:
    void ticketLoop();
    void becomeCandidateLocked();
    void becomeLeaderLocker();
    void recalculateCommitIndexLocked();
    void applyCommittedEntriesLocked();
    std::chrono::milliseconds randomElectionTimeout() const;

    void requestVoteFromPeer(NodeId peer, Term electionTerm, LogIndex lastLogIndex, Term lastLogTerm);
    void replicateToPeer(NodeId peer);
    void broadcastAppendEntries();

    NodeId id_;
    std::vector<PeerInfo> peers_;
    Storage& storage_;
    KVStore& kv_;
    Transport& transport_;
    Config config_;

    mutable std::mutex mutex;
    std::condition_variable commitCv_;

    Role role_ = Role::Follower;
    std::optional<NodeId> currentLeader_;
    LogIndex commitIndex_=0;
    LogIndex lastApplied_ =0;
    std::unordered_map<NodeId, LogIndex> nextIndex_;
    std::unordered_map<NodeId, LogIndex> matchIndex_;
    int votesReceived_=0;

    std::chrono::steady_clock::time_point lastHeardFromLeaderOrGrantedVote_;
    std::chrono::milliseconds currentElectionTimeout_;
    std::chrono::steady_clock::time_point lastHeartBeatBroadcast_;

    std::atomic<bool> stopFlag_{false};
    std::thread tickerThread_;
    mutable std::mt19937 rng_;

};
}