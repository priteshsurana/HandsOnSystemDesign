#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

namespace raft{
    class KVStore{
        public:
        void apply(const std::string& command);
        std::optional<std::string> get(const std::string& key) const;


        private:
        mutable std::mutex mutex;
        std::unordered_map<std::string, std::string> data_;

    };
}