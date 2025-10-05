# Tectra

> A modern C++ trading-infrastructure stack for real-world finance — combining a low-latency market-data feed handler, pre-trade risk checks, firm-wide kill switch, and deterministic replay engine into one cohesive, production-style system.

---

## 🚀 Project Description

**Tectra** is a compact yet realistic trading-platform core built in modern C++.  
It focuses on the invisible infrastructure that every serious trading firm relies on:

- **Feed Handler & Normaliser** — decodes ITCH/OUCH-like streams, manages sequencing and recovery, builds L2 books, and publishes a unified internal schema for downstream consumers.
- **Pre-Trade Risk Service** — microsecond-level rule checks for price bands, size/notional limits, credit caps, and per-venue throttles with hot-reloadable limits and full auditability.
- **Kill-Switch / Circuit-Breaker** — automatic and manual triggers that freeze or slow order flow, cancel open orders, or isolate venues with sub-millisecond propagation.
- **Deterministic Replay Engine** — append-only, checksummed journals with time-virtualised playback and golden-run diffing for post-incident analysis.

Built with C++20, lock-free shared-memory rings, FlatBuffers/Protobuf schemas, Prometheus metrics, and tamper-evident logging, **Tectra** demonstrates the real craft of systems engineering — correctness, speed, and observability.

---

## 🧠 What Makes Tectra Different?

- **Realistic, not flashy** — you can actually run it end-to-end: market data → risk → safety → replay.
- **Determinism first** — every event journaled, every replay identical; designed for root-cause analysis and reliability testing.
- **Dual-plane architecture** — binary fast path for low-latency data, structured control plane for operators and metrics.
- **Safety built in** — kill-switch triggers, rule hit-rates, and audit trails mirror real risk controls.
- **Composability** — each service stands alone yet integrates seamlessly; schemas and adapters keep interfaces stable.
- **Operability** — clear CLI/TUI tools for limit loading, kill-switch arming, and replay execution.
- **Portable** — no exotic dependencies; builds with CMake and runs on a single host.

---

## 🏗️ Core Design Principles

- **Low-latency by construction** — zero-copy I/O, cache-aligned data, bounded queues with backpressure, and minimal heap use on the hot path.  
- **Deterministic and reproducible** — identical outputs under identical inputs; fixed clock domains and seedable RNG.  
- **Contract-first schemas** — a single versioned message schema across services, strict validation at boundaries.  
- **Safety and correctness** — explicit rule logic, idempotent kill actions, and clear rejection reasons.  
- **Observability everywhere** — Prometheus metrics, structured logs, latency histograms, and per-rule counters.  
- **Graceful degradation** — predictable performance under load; no unbounded growth.  
- **Isolation and fault containment** — services communicate through narrow, testable interfaces.  
- **Auditability** — append-only journals with checksums and Merkle roots; operator actions recorded and verifiable.  
- **Testability as a feature** — unit, fuzz, and golden-replay tests ensure correctness under stress.  
- **Portability** — dependency-light, cross-platform, easy to deploy and extend.

---

## 🗺️ Roadmap

- [ ] 1) Foundations & Contracts
- [ ] 2) Market Data Ingest & Normaliser
- [ ] 3) Pre-Trade Risk Engine
- [ ] 4) MVP: Feed ↔ Risk Integration
- [ ] 5) Kill-Switch / Circuit-Breaker
- [ ] 6) Journaling & Deterministic Replay
- [ ] 7) Operator Tooling & Dashboards
- [ ] 8) Performance & Latency Engineering
- [ ] 9) Protocol Adapters & Gateways
- [ ] 10) Resilience & Fault Injection
- [ ] 11) Packaging & Deployment
- [ ] 12) Complete Stack v1.0

---

## 📍 Milestones

### 1) Foundations & Contracts

#### Scope
- [ ] Establish core repo structure (monorepo) and build system (CMake, clang-tidy, ASAN/UBSAN).
- [ ] Add common utilities (time, pinning, logging, config).
- [ ] Define contribution and coding standards.

#### Interfaces & Schema
- [ ] Define versioned internal schemas (FlatBuffers/Protobuf) for ticks, books, orders, verdicts, control.
- [ ] Document compatibility rules and versioning strategy.
- [ ] Provide codegen targets and CI checks for schema drift.

#### Data Path
- [ ] Implement shared-memory ring with bounded queues, backpressure, perf counters.
- [ ] Provide single-producer/single-consumer and MPMC variants.
- [ ] Add sequence numbers and loss/gap detection.

#### Control Plane
- [ ] Provide HTTP/gRPC scaffold with health/readiness endpoints.
- [ ] Expose /metrics (Prometheus) for every service.
- [ ] Add structured logging (JSON) and correlation IDs.

#### Storage & State
- [ ] Implement config loader with validation and defaults.
- [ ] Define directories for snapshots, journals, and logs.

#### Observability
- [ ] Add latency histograms (p50/p95/p99/p999) and queue-depth gauges.
- [ ] Provide example Grafana dashboards.

#### Testing
- [ ] Unit tests for schema serialisation/deserialisation.
- [ ] Property tests for ring buffer contract.
- [ ] CI pipeline with sanitizers and format/lint gates.

#### Exit Criteria
- [ ] Example publisher/consumer achieves >1M msgs/sec on localhost with metrics exposed.

---

### 2) Market Data Ingest & Normaliser

#### Scope
- [ ] Build ITCH (or synthetic ITCH-like) decoder.
- [ ] Implement sequencing, gap detection, and recovery.
- [ ] Build L2 book per instrument and publish normalised updates.

#### Interfaces & Schema
- [ ] Map wire frames → `NormalisedTick` / `BookUpdate`.
- [ ] Version book structures and document guarantees (e.g., monotonic sequence).

#### Data Path
- [ ] Zero-copy decode where possible; minimise allocations.
- [ ] Implement snapshot + incremental catch-up strategy.
- [ ] Partition by symbol to reduce contention.

#### Control Plane
- [ ] Endpoints to select symbols, set snapshot cadence, and trigger recovery.
- [ ] Health checks for input lag and sequence state.

#### Storage & State
- [ ] Periodic durable snapshots of book state.
- [ ] Fast warm-start from latest snapshot.

#### Observability
- [ ] Counters for gaps, resends, and dropped frames.
- [ ] Decode/dispatch latency metrics per symbol.

#### Testing
- [ ] Golden tests for decoder on canned corpora.
- [ ] Property tests on book invariants (price levels, total volume).
- [ ] Restart/warm-start correctness test.

#### Exit Criteria
- [ ] Sustained ≥1.0M msgs/sec/core decode on synthetic feed; warm start restores correct book state.

---

### 3) Pre-Trade Risk Engine

#### Scope
- [ ] Implement fast-path rule checks (price bands, max size/notional, credit, position, per-venue throttles, self-match prevent).
- [ ] Support dry-run mode for evaluation without blocking.

#### Interfaces & Schema
- [ ] `OrderRequest` → `RiskVerdict` with explicit rejection reasons.
- [ ] `LimitsUpdate` and ruleset management API.

#### Data Path
- [ ] In-memory state for limits and references.
- [ ] Snapshot references from normaliser for price bands.

#### Control Plane
- [ ] CRUD for limits with atomic hot-reload.
- [ ] Rule toggles and presets (per-instrument, per-venue).
- [ ] Health/metrics endpoints.

#### Storage & State
- [ ] Durable limits store (SQLite/Postgres optional).
- [ ] In-memory fast cache with versioning.

#### Observability
- [ ] p50/p95/p99 decision latency tracking.
- [ ] Per-rule hit/deny counters and distributions.

#### Testing
- [ ] Property tests per rule and rule-composition.
- [ ] Fuzz invalid frames and boundary values.
- [ ] Determinism tests under fixed seed.

#### Exit Criteria
- [ ] ≥100k orders/sec with p99 < 80 µs across 5 enabled rules.

---

### 4) MVP: Feed ↔ Risk Integration

#### Scope
- [ ] Integrate normaliser references into risk checks.
- [ ] Run end-to-end on one host via shared-memory rings.

#### Interfaces & Schema
- [ ] Validate schema contracts across services (ticks/books/orders/verdicts).
- [ ] Version lock for the MVP tag.

#### Data Path
- [ ] Single-command pipeline: ingest ticks → evaluate orders → emit verdicts.
- [ ] Bounded queues with backpressure.

#### Control Plane
- [ ] Unified CLI to boot services, load limits, start demo flow.
- [ ] Health aggregation endpoint.

#### Observability
- [ ] Combined dashboard (decode rate, queue depths, risk latencies).
- [ ] Scenario counters (accepted/rejected by reason).

#### Testing
- [ ] E2E golden run with fixed inputs and stable outputs.
- [ ] Soak test at target throughput.

#### Exit Criteria
- [ ] One-command MVP demo achieving advertised throughput and latency targets.

---

### 5) Kill-Switch / Circuit-Breaker

#### Scope
- [ ] Implement triggers (reject-rate, stale data age, latency spike, exposure jump, venue link-down, manual E-stop).
- [ ] Implement actions (block, cancel, slow-mode, isolate venue).

#### Interfaces & Schema
- [ ] `KillTrigger` / `KillAction` / `Ack` frames.
- [ ] RBAC roles for operators.

#### Data Path
- [ ] Sub-ms fan-out to subscribed gateways/services.
- [ ] Idempotent actions with acknowledgements.

#### Control Plane
- [ ] Operator TUI/CLI to arm, trigger, clear, and annotate reason.
- [ ] Dry-run mode for drills.

#### Storage & State
- [ ] Action ledger with tamper-evident records.
- [ ] Link action records to journals.

#### Observability
- [ ] Trigger-to-effect latency metrics.
- [ ] Per-action counts and failure/retry statistics.

#### Testing
- [ ] Chaos drills in sandbox.
- [ ] Dry-run validation and rollback scenarios.

#### Exit Criteria
- [ ] Local trigger-to-effect < 1 ms with reliable acknowledgements from all subscribers.

---

### 6) Journaling & Deterministic Replay

#### Scope
- [ ] Append-only, checksummed, memory-mapped journals for inputs/outputs.
- [ ] Time virtualisation (real-time, faster-than-real-time, step).

#### Interfaces & Schema
- [ ] Journal segment format with metadata (clock domain, seed, segment hash).
- [ ] `ReplayControl` commands and diff reports.

#### Data Path
- [ ] Capture feed, orders, verdicts, and kill events.
- [ ] Rehydrate state and replay to produce identical outputs.

#### Control Plane
- [ ] CLI to cut windows, rehydrate, replay, and emit RCA/diff report.
- [ ] Corruption detection and segment verification.

#### Storage & State
- [ ] Per-segment Merkle roots and index manifests.
- [ ] Retention/rotation policies (manual at this stage).

#### Observability
- [ ] Ingest/replay rates and durations.
- [ ] Divergence summaries by component.

#### Testing
- [ ] Golden-run bit-for-bit equality tests.
- [ ] Faulted/corrupted journal detection tests.

#### Exit Criteria
- [ ] ≥10× real-time replay on 1-hour capture with zero diffs vs golden.

---

### 7) Operator Tooling & Dashboards

#### Scope
- [ ] `tectractl` CLI and minimal TUI for live state/actions.
- [ ] RBAC integration hooks.

#### Interfaces & Schema
- [ ] Safe command channels for limits, kill, replay, snapshots.
- [ ] Confirmation flows for destructive actions.

#### Data Path
- [ ] Command dispatch with correlation IDs and timeouts.
- [ ] Idempotent retries and status tracking.

#### Control Plane
- [ ] Profiles for demo/perf/dev modes.
- [ ] Export/import of limits and scenarios.

#### Storage & State
- [ ] Command audit trails linked to journal segments.
- [ ] Snapshot/version history.

#### Observability
- [ ] Grafana dashboards (latency histograms, queue depths, rule hits, triggers).
- [ ] Alerting rules for error budgets and SLA breaches.

#### Testing
- [ ] Snapshot tests for CLI/TUI output.
- [ ] RBAC behaviour tests.

#### Exit Criteria
- [ ] Operators can run a full drill and generate an RCA report end-to-end.

---

### 8) Performance & Latency Engineering

#### Scope
- [ ] Tune hot paths with thread pinning, NUMA notes, custom allocators, batch I/O.
- [ ] Optional io_uring / AF_XDP experiments.

#### Interfaces & Schema
- [ ] Freeze schema for perf work; measure upgrade impact.
- [ ] Add perf profiles exporter.

#### Data Path
- [ ] Reduce allocations, improve cache locality, batch syscalls.
- [ ] Tune ring sizes and backpressure thresholds.

#### Control Plane
- [ ] Runtime toggles for batching, polling intervals, and timers.
- [ ] Perf harness CLI to drive workloads.

#### Storage & State
- [ ] Snapshot compaction and warm-start benchmarks.

#### Observability
- [ ] Flamegraphs and perf sched traces.
- [ ] Percentile SLO alerts and regressions.

#### Testing
- [ ] Performance regression suite with budget gates.
- [ ] Repeatable benchmarks with pinned environments.

#### Exit Criteria
- [ ] Feed p99 dispatch in single-digit µs for simple frames; risk p99 well under 80 µs at target throughput.

---

### 9) Protocol Adapters & Gateways

#### Scope
- [ ] FIX 4.4/5.0 adapter (QuickFIX or thin custom).
- [ ] SBE/FAST codec for compact market data.
- [ ] OUCH order-entry stub for testing.

#### Interfaces & Schema
- [ ] Wire → internal schema translators with strict validation.
- [ ] Session control events and resend requests.

#### Data Path
- [ ] Map messages without compromising latency.
- [ ] Persist sequence numbers/session stores.

#### Control Plane
- [ ] Adapter health, sequence, and resend controls.
- [ ] Dictionary/dialect configuration.

#### Storage & State
- [ ] Durable session state and recovery.
- [ ] Adapter logs and drop-copy hooks.

#### Observability
- [ ] Per-adapter error rates and resend counts.
- [ ] Session latency and throughput metrics.

#### Testing
- [ ] Conformance tests with canned dictionaries/corpora.
- [ ] Negative tests for invalid frames and edge cases.

#### Exit Criteria
- [ ] Interop demo with a FIX session and SBE-coded synthetic feed.

---

### 10) Resilience & Fault Injection

#### Scope
- [ ] Fault-injection flags and profiles for chaos scenarios.
- [ ] Graceful degradation paths.

#### Interfaces & Schema
- [ ] Scenario descriptors (venue outage, slow consumer, corrupted frame, clock skew).
- [ ] Error/event taxonomy across services.

#### Data Path
- [ ] Bounded queues; prefer backpressure to drops.
- [ ] Retries with jitter and circuit-breaking on adapters.

#### Control Plane
- [ ] Orchestrated chaos runs via CLI.
- [ ] Automated RCA report generation post-run.

#### Storage & State
- [ ] Partial snapshot recovery and reconciliation.
- [ ] State checks after recovery.

#### Observability
- [ ] Error budgets and recovery times tracked.
- [ ] SLA breach counters and alerts.

#### Testing
- [ ] CI chaos scenarios for core failure modes.
- [ ] Replay-based RCAs for each injected fault.

#### Exit Criteria
- [ ] All core scenarios pass with documented recovery behaviour and SLAs.

---

### 11) Packaging & Deployment

#### Scope
- [ ] One-line bootstrap (compose/supervisor) for full stack.
- [ ] Reproducible builds and signed artefacts.

#### Interfaces & Schema
- [ ] Versioned artefacts and schema compatibility matrix.
- [ ] Profiles for dev/perf/demo.

#### Data Path
- [ ] Default single-host config with sane limits.
- [ ] Sample datasets and demo flows.

#### Control Plane
- [ ] Startup ordering and health gating.
- [ ] Log rotation and retention guidance.

#### Storage & State
- [ ] Standard directories for journals, snapshots, logs.
- [ ] Cleanup and rotation scripts.

#### Observability
- [ ] Pre-baked dashboards and alerts included.
- [ ] Smoke-test on install.

#### Testing
- [ ] Install tests and example-run validation.
- [ ] Checksums and SBOM generation.

#### Exit Criteria
- [ ] Full demo stack starts locally with one command; artefacts and checksums published.

---

### 12) Complete Stack v1.0

#### Scope
- [ ] Integrated feed → risk → kill-switch → journal; replay for RCA and regression.
- [ ] Documentation and release assets.

#### Interfaces & Schema
- [ ] Freeze v1.0 schemas and publish migration notes.
- [ ] Public API docs for control endpoints.

#### Data Path
- [ ] Proven throughput/latency targets under soak.
- [ ] Snapshot/journal lifecycle documented.

#### Control Plane
- [ ] Operators manage limits, drills, replay via `tectractl`.
- [ ] RBAC examples and audit workflows.

#### Storage & State
- [ ] Retention and rotation guidance.
- [ ] Data export to Parquet/ClickHouse (optional).

#### Observability
- [ ] Dashboards cover p50/p95/p99, rule hits, triggers, queues.
- [ ] Alert rules validated during drills.

#### Testing
- [ ] E2E golden suite, chaos scenarios, performance gates.
- [ ] Reproducible RCAs from captured incidents.

#### Exit Criteria
- [ ] Tagged v1.0 release with docs, demo dataset, and short walkthrough video.
