#pragma once

#include "raft_types.h"
#include <optional>
#include <string>
#include <vector>

namespace raft{
class Storage{
    public:
    explicit Storage(const std::string& dataDir);

    Term currentTerm() const;
    std::optional<NodeId> votedFor() const;

    void setTermAndVotedFor(Term term, std::optional<NodeId> votedFor);

    LogIndex lastLogIndex() const;
    Term lastLogTerm() const;
    Term termAt(LogIndex index) const;

    std::optional<LogEntry> entryAt(LogIndex index) const;
    std::vector<LogEntry> entriesFrom(LogIndex from) const;

    bool hasMatchingEntry(LogIndex prevLogIndex, Term prevLogTerm) const;

    LogIndex appendNew(Term term, const std::string& command);

    void overwriteFrom(LogIndex startIndex, const std::vector<LogEntry>& entries);


    private:
    void loadFromDisk();
    void writeMetadata();
    void appendEntryToFile();
    void rewriteLogFile();
    void fsyncPath(const std::string& path);

    std::string dataDir_;
    std::string metaPath_;
    std::string logPath_;

    mutable std::mutex mutex_;
    Term currentTerm_=0;
    std::optional<NodeId> votedFor_;
    std::vector<LogEntry> log_;
    

};
}