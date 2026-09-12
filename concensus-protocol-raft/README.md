# Concensus protocol(Raft) implementation

This is a minimal dependency  free Raft implementation in C++17 where I have focused on leader election, log replication, crash safe persistence, and a tiny replicated key-value store on top. Few things might appear non-obvious which has a comment pointing at some specific rule in [Raft paper](https://raft.github.io/raft.pdf) it implements.

I would highly recommend going through my article on [consensus protocol](https://dev.to/priteshsurana/) before trying to understand this implementation.

## What's here and what isn't

**Implemented:** leader election with randomized timeouts and terms, log replication with the consistency check and conflict resolution, the majority-commit rule, crash-safe persistence(fsync log + metadata), and a plain-text RPC/client protocol you can drive by hand with nc.

**Not implemented:** linearizable reads, log compaction/snapshotting, cluster membership changes (joint consensus), and the optional fast log-backtracking optimization.

## Architecture

TODO:
