# **Systems Engineering Lab**

A collection of hands-on experiments, implementations, benchmarks, and prototypes exploring **system design, distributed systems, databases, concurrency, networking, and infrastructure**.

The goal of this repository is simple:

> **Don't just learn how a system works. Build a simplified version, break it, measure it, and understand why it behaves the way it does.**

This is a personal engineering lab for turning system-design concepts from theory into something that can be implemented and measured.

**In an age of AI-assisted coding, I believe fundamentals matter more than ever. Breaking down complex systems into simple building blocks and intuitive ideas is what allows us to understand, reason about, and build systems rather than simply generate code for them.**

---

## **What is this repository?**

Most system design material stops at architecture diagrams:

```text
Client → Load Balancer → Service → Cache → Database
```

That is useful, but it doesn't answer many of the questions that matter when actually building systems:

* What happens when a node fails?

* Where does contention appear?

* How does latency change as load increases?

* What consistency guarantees are actually provided?

* What happens during network partitions?

* How does a B+Tree behave differently from an LSM tree?

* What does a consensus protocol actually require?

* Where do locks become a bottleneck?

* What are the real trade-offs behind a design decision?

This repository is where I try to study and answer those questions through **code and experiments**.

---

## **Experiments**

Each project focuses on a specific systems concept and attempts to explore it through implementation, measurement, or both.

### **Database Internals & Benchmarking**

A comparative benchmark of:

* PostgreSQL

* MongoDB

* Cassandra

The goal was not simply to compare database benchmarks found online, but to understand how different database architectures behave under different workloads.

Experiments include scenarios such as:

* Read-heavy workloads

* Write-heavy workloads

* Sequential vs random access

* Different data sizes

* Different concurrency levels

* Indexing effects

* Latency and throughput

* Storage-engine characteristics

The experiments are accompanied by analysis of **why** the databases behave differently rather than treating benchmark numbers as isolated results.

---

### **Consensus Protocol Implementation**

A hands-on implementation of a distributed consensus protocol.

The focus is on understanding the mechanics behind consensus rather than treating consensus as a black box.

Areas explored include:

* Leader election

* Replication

* Terms / epochs

* Log replication

* Quorum-based decisions

* Failure handling

* Node crashes

* Network delays

* Message loss

* State transitions

The implementation is intentionally simplified compared with production systems, with the goal of making the underlying protocol easier to reason about.

---

A distributed system that works only when everything works is not very interesting.

In these experiments, I may intentionally introduce:

* Node failures

* Network delays

* Dropped messages

* Duplicated messages

* Concurrent requests

* Resource exhaustion

* Slow consumers

* Partial failures

---

## **Current Experiments**

| Area                | Experiment                         | Focus                                         |
| ------------------- | ---------------------------------- | --------------------------------------------- |
| Databases           | PostgreSQL vs MongoDB vs Cassandra | Storage engines, workloads, performance       |
| Distributed Systems | Consensus Protocol                 | Replication, leader election, fault tolerance |
| More coming         | —                                  | —                                             |

---

## **What This Repository Is Not**

This is not intended to be:

* A collection of system-design interview diagrams

* Production-ready implementations of distributed systems

* A collection of tutorials copied from existing implementations

* A benchmark leaderboard

The implementations are primarily **learning and experimentation vehicles**.

The objective is to develop the ability to go from:

```text
Concept

   ↓

Architecture

   ↓

Implementation

   ↓

Experiment

   ↓

Failure

   ↓

Measurement

   ↓

Understanding
```

---

## **Long-Term Goal**

Over time, this repository should become a collection of progressively deeper systems experiments.

The end goal is not to implement every distributed system or database.

It is to build enough of them to develop strong intuition for:

* **Correctness**

* **Concurrency**

* **Distributed coordination**

* **Failure handling**

* **Data consistency**

* **Storage**

* **Performance**

* **Scalability**

* **Architectural trade-offs**

Ultimately:

> **A system design should not remain a diagram. It should be something I can reason about from the implementation, observe through experiments, and explain from first principles.**
