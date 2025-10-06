# Tectra

> A modern C++ trading-infrastructure stack for real-world finance — combining a low-latency market-data feed handler, pre-trade risk checks, firm-wide kill switch, deterministic replay engine, **strategy execution framework, backtesting engine, and signal research toolkit** into one cohesive, production-style system.

---

## 🚀 Project Description

**Tectra** is a compact yet realistic trading-platform core built in modern C++.  
It focuses on the invisible infrastructure that every serious trading firm relies on, **plus the strategy execution layer that sits on top of it**:

- **Feed Handler & Normaliser** — decodes ITCH/OUCH-like streams, manages sequencing and recovery, builds L2 books, and publishes a unified internal schema for downstream consumers.
- **Pre-Trade Risk Service** — microsecond-level rule checks for price bands, size/notional limits, credit caps, and per-venue throttles with hot-reloadable limits and full auditability.
- **Kill-Switch / Circuit-Breaker** — automatic and manual triggers that freeze or slow order flow, cancel open orders, or isolate venues with sub-millisecond propagation.
- **Deterministic Replay Engine** — append-only, checksummed journals with time-virtualised playback and golden-run diffing for post-incident analysis.
- **Strategy Execution Framework** — plugin architecture for trading strategies with signal generation, order management, position tracking, and P&L calculation.
- **Backtesting Engine** — time-virtualised historical replay with simulated fills, realistic slippage models, and transaction cost analysis.
- **Signal Library & Research Tools** — reusable building blocks for technical indicators, statistical arbitrage, mean reversion, momentum, and ML feature extraction.

Built with C++20, lock-free shared-memory rings, FlatBuffers/Protobuf schemas, Prometheus metrics, and tamper-evident logging, **Tectra** demonstrates the real craft of systems engineering — correctness, speed, observability, **and the practical application of quantitative trading strategies**.

---

## 🧠 What Makes Tectra Different?

- **Realistic, not flashy** — you can actually run it end-to-end: market data → signal generation → strategy logic → risk → execution → P&L tracking → replay.
- **Determinism first** — every event journaled, every replay identical; designed for root-cause analysis, strategy debugging, and reliability testing.
- **Dual-plane architecture** — binary fast path for low-latency data, structured control plane for operators and metrics.
- **Safety built in** — kill-switch triggers, rule hit-rates, and audit trails mirror real risk controls.
- **Composability** — each service stands alone yet integrates seamlessly; schemas and adapters keep interfaces stable. Strategies are plugins that hot-reload without recompiling the platform.
- **Operability** — clear CLI/TUI tools for limit loading, kill-switch arming, replay execution, **strategy deployment, backtest analysis, and P&L reporting**.
- **Portable** — no exotic dependencies; builds with CMake and runs on a single host.
- **Full-stack coverage** — bridges infrastructure engineering and quantitative development, showing how strategies integrate with the platform they depend on.

---

## 🏗️ Core Design Principles

- **Low-latency by construction** — zero-copy I/O, cache-aligned data, bounded queues with backpressure, and minimal heap use on the hot path.  
- **Deterministic and reproducible** — identical outputs under identical inputs; fixed clock domains and seedable RNG.  
- **Contract-first schemas** — a single versioned message schema across services, strict validation at boundaries.  
- **Safety and correctness** — explicit rule logic, idempotent kill actions, clear rejection reasons, and position limit enforcement.  
- **Observability everywhere** — Prometheus metrics, structured logs, latency histograms, per-rule counters, **per-strategy P&L, Sharpe ratios, and drawdown tracking**.  
- **Graceful degradation** — predictable performance under load; no unbounded growth.  
- **Isolation and fault containment** — services communicate through narrow, testable interfaces. Strategies run in isolated contexts with resource limits.  
- **Auditability** — append-only journals with checksums and Merkle roots; operator actions recorded and verifiable. **Every trade attributed to a strategy with full lineage.**  
- **Testability as a feature** — unit, fuzz, golden-replay, and property-based tests ensure correctness under stress. **Strategy backtests act as integration tests.**  
- **Portability** — dependency-light, cross-platform, easy to deploy and extend.  
- **Research-to-production pipeline** — seamless workflow from signal discovery to backtest to live deployment with continuous monitoring.

---

## 🗺️ Roadmap

- [ ] 1) Foundations & Contracts
- [ ] 2) Market Data Ingest & Normaliser
- [ ] 3) Pre-Trade Risk Engine
- [ ] 4) MVP: Feed ↔ Risk Integration
- [ ] 5) Strategy Execution Framework & Signal Library
- [ ] 6) Backtesting Engine & Historical Replay
- [ ] 7) Kill-Switch / Circuit-Breaker
- [ ] 8) Advanced Strategy Examples & Research Tools
- [ ] 9) Operator Tooling & Dashboards
- [ ] 10) Performance & Latency Engineering
- [ ] 11) Protocol Adapters & Gateways
- [ ] 12) Resilience & Fault Injection
- [ ] 13) Packaging & Deployment
- [ ] 14) Complete Stack v1.0

---

## 📍 Milestones

### 1) Foundations & Contracts

#### Scope
- [ ] Establish core repo structure (monorepo) and build system (CMake, clang-tidy, ASAN/UBSAN).
- [ ] Add common utilities (time, pinning, logging, config).
- [ ] Define contribution and coding standards.

#### Interfaces & Schema
- [ ] Define versioned internal schemas (FlatBuffers/Protobuf) for ticks, books, orders, verdicts, control.
- [ ] Add schemas for signals, positions, fills, P&L, and backtest configs/results.
- [ ] Document compatibility rules and versioning strategy.
- [ ] Provide codegen targets and CI checks for schema drift.

#### Data Path
- [ ] Implement shared-memory ring with bounded queues, backpressure, perf counters.
- [ ] Provide single-producer/single-consumer and MPMC variants.
- [ ] Add sequence numbers and loss/gap detection.
- [ ] Add tagged message routing for multi-strategy dispatch.

#### Control Plane
- [ ] Provide HTTP/gRPC scaffold with health/readiness endpoints.
- [ ] Expose /metrics (Prometheus) for every service.
- [ ] Add structured logging (JSON) and correlation IDs.
- [ ] Add /strategies endpoint for live strategy state and P&L.

#### Storage & State
- [ ] Implement config loader with validation and defaults.
- [ ] Define directories for snapshots, journals, and logs.
- [ ] Add strategy plugin directory with hot-reload and validation.

#### Observability
- [ ] Add latency histograms (p50/p95/p99/p999) and queue-depth gauges.
- [ ] Provide example Grafana dashboards.
- [ ] Add per-strategy metrics: orders, fills, slippage, P&L, Sharpe.

#### Testing
- [ ] Unit tests for schema serialisation/deserialisation.
- [ ] Property tests for ring buffer contract.
- [ ] CI pipeline with sanitizers and format/lint gates.
- [ ] Property tests for position tracking invariants.

#### Exit Criteria
- [ ] Example publisher/consumer achieves >1M msgs/sec on localhost with metrics exposed.
- [ ] Strategy plugin handles 1M ticks/sec with <5µs overhead per signal.

---

### 2) Market Data Ingest & Normaliser

#### Scope
- [ ] Build ITCH (or synthetic ITCH-like) decoder.
- [ ] Implement sequencing, gap detection, and recovery.
- [ ] Build L2 book per instrument and publish normalised updates.
- [ ] Compute derived metrics: mid-price, spread, imbalance, VWAP, book pressure.

#### Interfaces & Schema
- [ ] Map wire frames → `NormalisedTick` / `BookUpdate`.
- [ ] Version book structures and document guarantees (e.g., monotonic sequence).
- [ ] Extend schema with timestamps, trade direction, and multi-level book features.

#### Data Path
- [ ] Zero-copy decode where possible; minimise allocations.
- [ ] Implement snapshot + incremental catch-up strategy.
- [ ] Partition by symbol to reduce contention.
- [ ] Publish tick-by-tick and aggregated bars (1s/5s/1m intervals).

#### Control Plane
- [ ] Endpoints to select symbols, set snapshot cadence, and trigger recovery.
- [ ] Health checks for input lag and sequence state.
- [ ] Add /book/{symbol} endpoint for current book and recent trades.

#### Storage & State
- [ ] Periodic durable snapshots of book state.
- [ ] Fast warm-start from latest snapshot.
- [ ] Store compressed historical ticks for backtesting with window-based queries.

#### Observability
- [ ] Counters for gaps, resends, and dropped frames.
- [ ] Decode/dispatch latency metrics per symbol.
- [ ] Track data quality: spread percentiles, tick rates, depth distribution.

#### Testing
- [ ] Golden tests for decoder on canned corpora.
- [ ] Property tests on book invariants (price levels, total volume).
- [ ] Restart/warm-start correctness test.
- [ ] Fuzz with malformed messages and verify recovery semantics.

#### Exit Criteria
- [ ] Sustained ≥1.0M msgs/sec/core decode on synthetic feed; warm start restores correct book state.
- [ ] Derived metrics published within 2µs of tick receipt; match golden tests.

---

### 3) Pre-Trade Risk Engine

#### Scope
- [ ] Implement fast-path rule checks (price bands, max size/notional, credit, position, per-venue throttles, self-match prevent).
- [ ] Support dry-run mode for evaluation without blocking.
- [ ] Add per-strategy position tracking and per-strategy risk limits.

#### Interfaces & Schema
- [ ] `OrderRequest` → `RiskVerdict` with explicit rejection reasons.
- [ ] `LimitsUpdate` and ruleset management API.
- [ ] Add strategy risk profile schema with per-strategy limits and filters.

#### Data Path
- [ ] In-memory state for limits and references.
- [ ] Snapshot references from normaliser for price bands.
- [ ] Maintain per-strategy position ledger with avg entry price and P&L.

#### Control Plane
- [ ] CRUD for limits with atomic hot-reload.
- [ ] Rule toggles and presets (per-instrument, per-venue).
- [ ] Health/metrics endpoints.
- [ ] Add /risk/strategies/{id} for positions and risk utilization.

#### Storage & State
- [ ] Durable limits store (SQLite/Postgres optional).
- [ ] In-memory fast cache with versioning.
- [ ] Persist position snapshots and journal fills for crash recovery.

#### Observability
- [ ] p50/p95/p99 decision latency tracking.
- [ ] Per-rule hit/deny counters and distributions.
- [ ] Per-strategy metrics: orders, accepts, rejects, positions, P&L, drawdown.

#### Testing
- [ ] Property tests per rule and rule-composition.
- [ ] Fuzz invalid frames and boundary values.
- [ ] Determinism tests under fixed seed.
- [ ] Simulate fills and verify position tracking correctness.

#### Exit Criteria
- [ ] ≥100k orders/sec with p99 < 80 µs across 5 enabled rules.
- [ ] Per-strategy position tracking adds <10µs overhead; snapshots restore in <100ms.

---

### 4) MVP: Feed ↔ Risk Integration

#### Scope
- [ ] Integrate normaliser references into risk checks.
- [ ] Run end-to-end on one host via shared-memory rings.
- [ ] Add simple passthrough strategy for pipeline validation.

#### Interfaces & Schema
- [ ] Validate schema contracts across services (ticks/books/orders/verdicts).
- [ ] Version lock for the MVP tag.
- [ ] Add strategy order schema linking orders to signals for lineage tracking.

#### Data Path
- [ ] Single-command pipeline: ingest ticks → evaluate orders → emit verdicts.
- [ ] Bounded queues with backpressure.
- [ ] Extend pipeline: ticks → strategy → orders → risk → verdicts with full lineage.

#### Control Plane
- [ ] Unified CLI to boot services, load limits, start demo flow.
- [ ] Health aggregation endpoint.
- [ ] Add --enable-strategy flag to toggle strategy execution.

#### Observability
- [ ] Combined dashboard (decode rate, queue depths, risk latencies).
- [ ] Scenario counters (accepted/rejected by reason).
- [ ] Strategy trace viewer linking ticks to signals to orders to fills.

#### Testing
- [ ] E2E golden run with fixed inputs and stable outputs.
- [ ] Soak test at target throughput.
- [ ] Verify passthrough strategy generates expected orders from synthetic ticks.

#### Exit Criteria
- [ ] One-command MVP demo achieving advertised throughput and latency targets.
- [ ] Passthrough strategy: 1M ticks/sec with <20µs tick-to-order latency (p99).

---

### 5) Strategy Execution Framework & Signal Library

#### Scope
- [ ] Design strategy plugin API as shared libraries implementing IStrategy interface.
- [ ] Implement strategy lifecycle: load, init, on_tick, on_fill, on_timer, shutdown.
- [ ] Build order management: submit_order(), cancel_order(), modify_order().
- [ ] Implement position manager: get_position(), get_pnl(), get_open_orders().
- [ ] Create signal library: SMA, EMA, RSI, MACD, Bollinger, Z-score, correlation.
- [ ] Add example strategies: MA crossover, mean reversion, pairs trading, market-making.

#### Interfaces & Schema
- [ ] IStrategy interface with on_tick(), on_fill(), on_timer(), get_config(), get_state().
- [ ] Signal schema: timestamp, symbol, type, confidence, metadata.
- [ ] StrategyConfig schema: parameters, symbol universe, risk limits, execution mode.
- [ ] StrategyState schema: serializable state for crash recovery.

#### Data Path
- [ ] Feed publishes ticks → runtime dispatches to strategies → signals → orders → risk.
- [ ] Strategies run in isolated contexts with CPU/memory limits.
- [ ] Strategy sandbox for testing against synthetic data without live execution.

#### Control Plane
- [ ] CLI: strategy load/deploy/pause/resume/stop/reload/list/inspect.
- [ ] Hot-reload: update parameters without restart via on_config_update().
- [ ] Dry-run mode: strategies emit signals but orders are logged, not submitted.

#### Storage & State
- [ ] Strategy plugin directory: strategies/<name>/lib.so, config.json, README.
- [ ] Periodic state snapshots; restore from latest on crash.
- [ ] Journal every signal emission for replay and attribution.

#### Observability
- [ ] Per-strategy dashboards: signals, orders, fills, slippage, P&L, Sharpe, drawdown, win rate.
- [ ] Health checks: responsiveness, stuck detection, memory leak monitoring.
- [ ] Trace signals to orders for debugging.

#### Testing
- [ ] Unit tests for signal library vs reference implementations (TA-Lib).
- [ ] Strategy contract tests: load, send ticks, verify method calls.
- [ ] Property tests: strategies respect symbol universe and position limits.
- [ ] Fuzz with random ticks/fills/timers; verify no crashes or leaks.

#### Exit Criteria
- [ ] Strategy plugin: runtime load, 1M ticks/sec, <10µs signal overhead, correct positions.
- [ ] MA-crossover example: loads <100ms, correct signals, >0% P&L on synthetic data.
- [ ] Signal library: indicators within 1% of TA-Lib on golden data.

---

### 6) Backtesting Engine & Historical Replay

#### Scope
- [ ] Extend replay for backtest mode: replay ticks, run strategies, simulate fills, compute P&L.
- [ ] Implement fill simulator: market orders at best bid/ask, limit orders with queue modeling.
- [ ] Add transaction cost analysis: fees, spread costs, market impact, opportunity cost.
- [ ] Append-only, checksummed, memory-mapped journals for inputs/outputs.
- [ ] Time virtualisation: real-time, 10x, 100x, 1000x, or instant replay.

#### Interfaces & Schema
- [ ] Journal segment format with metadata (clock domain, seed, segment hash).
- [ ] ReplayControl commands and diff reports.
- [ ] BacktestConfig: date range, symbols, strategies, capital, slippage, fees, speed.
- [ ] BacktestResult: P&L, Sharpe, drawdown, win rate, trades, per-trade attribution.

#### Data Path
- [ ] Capture feed, orders, verdicts, and kill events.
- [ ] Rehydrate state and replay to produce identical outputs.
- [ ] Backtest mode: read historical ticks, run strategies, simulate fills, track P&L.
- [ ] Support partial-day backtests for debugging specific windows.

#### Control Plane
- [ ] CLI to cut windows, rehydrate, replay, and emit RCA/diff report.
- [ ] Corruption detection and segment verification.
- [ ] Backtest CLI: run with config, output results, support batch mode.
- [ ] Interactive viewer: step tick-by-tick, visualize state and P&L.

#### Storage & State
- [ ] Per-segment Merkle roots and index manifests.
- [ ] Retention/rotation policies (manual at this stage).
- [ ] Store backtest results in SQLite; query API for comparisons.
- [ ] Compress historical ticks (LZ4/Zstd); decompress on replay.

#### Observability
- [ ] Ingest/replay rates and durations.
- [ ] Divergence summaries by component.
- [ ] Backtest progress tracking with estimated completion time.
- [ ] Validate backtest P&L vs live P&L; flag divergences.

#### Testing
- [ ] Golden-run bit-for-bit equality tests.
- [ ] Faulted/corrupted journal detection tests.
- [ ] Backtest determinism: same config → identical results.
- [ ] Backtest realism: compare simulated vs actual fills; measure error.

#### Exit Criteria
- [ ] ≥10× real-time replay on 1-hour capture with zero diffs vs golden.
- [ ] Backtest: 1 day (1M ticks) in <10s at 100x; fills within 5% of actuals.
- [ ] Results include P&L curve, drawdown, per-trade ledger, metrics, TCA breakdown.

---

### 7) Kill-Switch / Circuit-Breaker

#### Scope
- [ ] Implement triggers (reject-rate, stale data, latency spike, exposure jump, venue down, manual).
- [ ] Implement actions (block, cancel, slow-mode, isolate venue).
- [ ] Add strategy-level triggers: max daily loss, max drawdown, unusual patterns.
- [ ] Add strategy-level actions: pause, flatten positions, force-liquidate.

#### Interfaces & Schema
- [ ] KillTrigger / KillAction / Ack frames.
- [ ] RBAC roles for operators.
- [ ] StrategyKillTrigger: strategy ID, reason, state, timestamp.
- [ ] StrategyKillAction: action type, confirmation required, rollback procedure.

#### Data Path
- [ ] Sub-ms fan-out to subscribed gateways/services.
- [ ] Idempotent actions with acknowledgements.
- [ ] Strategy runtime subscribes to kills; invokes on_kill(), force-stop on timeout.

#### Control Plane
- [ ] Operator TUI/CLI to arm, trigger, clear, and annotate reason.
- [ ] Dry-run mode for drills.
- [ ] /kill/strategies/{id}/trigger endpoint with reason and confirmation.
- [ ] Kill-switch dashboard: active triggers, armed conditions, recent events, health.

#### Storage & State
- [ ] Action ledger with tamper-evident records.
- [ ] Link action records to journals.
- [ ] Store strategy kills: who, why, action, state, positions before/after.

#### Observability
- [ ] Trigger-to-effect latency metrics.
- [ ] Per-action counts and failure/retry statistics.
- [ ] Per-strategy kill metrics: trigger count, flatten time, P&L at kill vs 1min later.

#### Testing
- [ ] Chaos drills in sandbox.
- [ ] Dry-run validation and rollback scenarios.
- [ ] Strategy kill tests: inject conditions, verify pause/flatten timing and correctness.

#### Exit Criteria
- [ ] Local trigger-to-effect < 1 ms with reliable acks from all subscribers.
- [ ] Strategy kill: trigger → pause <50ms, flatten <500ms, no orphaned orders.

---

### 8) Advanced Strategy Examples & Research Tools

#### Scope
- [ ] Implement 5+ example strategies: MA crossover, Bollinger reversion, pairs trading, market-making, breakout.
- [ ] Build research toolkit: correlation scanner, cointegration tester, feature extractor.
- [ ] Add alpha decay analyzer and regime detector (HMM/clustering).

#### Interfaces & Schema
- [ ] ResearchSignal schema with metadata and feature vectors.
- [ ] FeatureVector schema: timestamp, symbol, features array, labels.
- [ ] PairCandidate schema: symbols, correlation, cointegration, half-life, hedge ratio.

#### Data Path
- [ ] Research tools run offline on historical data; output CSV/JSON/Parquet.
- [ ] Strategies consume signal library (same indicators in research and live).

#### Control Plane
- [ ] CLI: research correlation, cointegration, features with customizable windows.
- [ ] Jupyter integration: export results to Parquet for visualization.

#### Storage & State
- [ ] Research outputs in research/ directory with timestamped subdirectories.
- [ ] Feature datasets in Parquet for efficient querying.

#### Observability
- [ ] Research job tracking: running jobs, progress, estimated completion.
- [ ] Signal quality metrics: backtest candidates, rank by Sharpe, flag overfitting.

#### Testing
- [ ] Strategy correctness on synthetic data: trending → correct signals.
- [ ] Research tool validation vs numpy/statsmodels/TA-Lib.
- [ ] Overfitting detection: random signals → unprofitable backtests.

#### Exit Criteria
- [ ] 5 strategies implemented with positive Sharpe on out-of-sample data.
- [ ] Correlation scanner: 100 symbols in <10s; feature extractor: 50 features, 1yr data in <30s.
- [ ] Documented workflow: signal discovery → backtest → deploy → monitor.

---

### 9) Operator Tooling & Dashboards

#### Scope
- [ ] tectractl CLI and minimal TUI for live state/actions.
- [ ] RBAC integration hooks.
- [ ] Extend CLI with strategy, backtest, and research commands.

#### Interfaces & Schema
- [ ] Safe command channels for limits, kill, replay, snapshots.
- [ ] Confirmation flows for destructive actions.
- [ ] Command schemas for strategy deployment, params, positions, P&L.

#### Data Path
- [ ] Command dispatch with correlation IDs and timeouts.
- [ ] Idempotent retries and status tracking.

#### Control Plane
- [ ] Profiles for demo/perf/dev modes.
- [ ] Export/import of limits and scenarios.
- [ ] Profiles for paper-trading, live-trading, and backtest modes.
- [ ] Strategy deployment workflow: validate → backtest → review → deploy → monitor → scale.

#### Storage & State
- [ ] Command audit trails linked to journal segments.
- [ ] Snapshot/version history.
- [ ] Strategy deployment history: who, when, config, outcome over time.

#### Observability
- [ ] Grafana dashboards (latency, queues, rules, triggers).
- [ ] Alerting rules for error budgets and SLA breaches.
- [ ] Strategy dashboards: P&L curves, Sharpe, drawdown, trade history, signal quality.
- [ ] Comparative dashboards: backtest vs live performance for deployed strategies.

#### Testing
- [ ] Snapshot tests for CLI/TUI output.
- [ ] RBAC behaviour tests.
- [ ] End-to-end workflow tests: deploy strategy → monitor → kill → analyze.

#### Exit Criteria
- [ ] Operators run full drill and generate RCA report end-to-end.
- [ ] Strategy dashboard: real-time P&L, alerts on limit breaches, drill-down to trades.
- [ ] Deployment workflow: backtest → approval → live monitoring in <30min.

---

### 10) Performance & Latency Engineering

#### Scope
- [ ] Tune hot paths: thread pinning, NUMA, custom allocators, batch I/O.
- [ ] Optional io_uring / AF_XDP experiments.
- [ ] Profile and optimize strategy execution overhead.

#### Interfaces & Schema
- [ ] Freeze schema for perf work; measure upgrade impact.
- [ ] Add perf profiles exporter.

#### Data Path
- [ ] Reduce allocations, improve cache locality, batch syscalls.
- [ ] Tune ring sizes and backpressure thresholds.
- [ ] Optimize signal library: vectorize indicators, reduce branching.

#### Control Plane
- [ ] Runtime toggles for batching, polling intervals, and timers.
- [ ] Perf harness CLI to drive workloads.
- [ ] Strategy profiling: per-indicator latency, memory footprint.

#### Storage & State
- [ ] Snapshot compaction and warm-start benchmarks.

#### Observability
- [ ] Flamegraphs and perf sched traces.
- [ ] Percentile SLO alerts and regressions.
- [ ] Per-strategy CPU/memory usage tracking.

#### Testing
- [ ] Performance regression suite with budget gates.
- [ ] Repeatable benchmarks with pinned environments.
- [ ] Strategy benchmarks: X ticks/sec with Y strategies at Z latency.

#### Exit Criteria
- [ ] Feed p99 dispatch in single-digit µs; risk p99 well under 80 µs.
- [ ] Strategy execution: 10 concurrent strategies, 1M ticks/sec, <15µs avg overhead.

---

### 11) Protocol Adapters & Gateways

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

### 12) Resilience & Fault Injection

#### Scope
- [ ] Fault-injection flags and profiles for chaos scenarios.
- [ ] Graceful degradation paths.
- [ ] Inject strategy faults: stuck indicators, memory leaks, slow callbacks.

#### Interfaces & Schema
- [ ] Scenario descriptors (venue outage, slow consumer, corrupted frame, clock skew).
- [ ] Error/event taxonomy across services.
- [ ] Strategy fault descriptors: callback timeouts, state corruption, OOM.

#### Data Path
- [ ] Bounded queues; prefer backpressure to drops.
- [ ] Retries with jitter and circuit-breaking on adapters.
- [ ] Strategy isolation: faulted strategy doesn't crash platform.

#### Control Plane
- [ ] Orchestrated chaos runs via CLI.
- [ ] Automated RCA report generation post-run.
- [ ] Strategy chaos: inject faults, verify isolation and recovery.

#### Storage & State
- [ ] Partial snapshot recovery and reconciliation.
- [ ] State checks after recovery.

#### Observability
- [ ] Error budgets and recovery times tracked.
- [ ] SLA breach counters and alerts.
- [ ] Per-strategy fault tracking: timeout rate, recovery time.

#### Testing
- [ ] CI chaos scenarios for core failure modes.
- [ ] Replay-based RCAs for each injected fault.
- [ ] Strategy chaos tests: kill strategy mid-tick, verify cleanup.

#### Exit Criteria
- [ ] All core scenarios pass with documented recovery behaviour and SLAs.
- [ ] Strategy faults isolated: one bad strategy doesn't affect others or platform.

---

### 13) Packaging & Deployment

#### Scope
- [ ] One-line bootstrap (compose/supervisor) for full stack.
- [ ] Reproducible builds and signed artefacts.

#### Interfaces & Schema
- [ ] Versioned artefacts and schema compatibility matrix.
- [ ] Profiles for dev/perf/demo.

#### Data Path
- [ ] Default single-host config with sane limits.
- [ ] Sample datasets and demo flows.
- [ ] Include example strategies and historical data for backtesting.

#### Control Plane
- [ ] Startup ordering and health gating.
- [ ] Log rotation and retention guidance.

#### Storage & State
- [ ] Standard directories for journals, snapshots, logs.
- [ ] Cleanup and rotation scripts.

#### Observability
- [ ] Pre-baked dashboards and alerts included.
- [ ] Smoke-test on install.
- [ ] Demo includes live strategy with P&L visualization.

#### Testing
- [ ] Install tests and example-run validation.
- [ ] Checksums and SBOM generation.
- [ ] Verify demo: start → run strategies → view P&L → kill → replay.

#### Exit Criteria
- [ ] Full demo stack starts locally with one command; artefacts published.
- [ ] Demo runs example strategies on synthetic data with live P&L dashboard.

---

### 14) Complete Stack v1.0

#### Scope
- [ ] Integrated feed → signal → risk → execution → P&L; replay for RCA and regression.
- [ ] Documentation and release assets.

#### Interfaces & Schema
- [ ] Freeze v1.0 schemas and publish migration notes.
- [ ] Public API docs for control endpoints.

#### Data Path
- [ ] Proven throughput/latency targets under soak.
- [ ] Snapshot/journal lifecycle documented.

#### Control Plane
- [ ] Operators manage limits, drills, replay via tectractl.
- [ ] RBAC examples and audit workflows.
- [ ] Strategy lifecycle management: deploy, monitor, kill, analyze.

#### Storage & State
- [ ] Retention and rotation guidance.
- [ ] Data export to Parquet/ClickHouse (optional).

#### Observability
- [ ] Dashboards cover p50/p95/p99, rules, triggers, queues, strategies, P&L.
- [ ] Alert rules validated during drills.

#### Testing
- [ ] E2E golden suite, chaos scenarios, performance gates.
- [ ] Reproducible RCAs from captured incidents.
- [ ] Strategy regression suite: backtests as integration tests.

#### Exit Criteria
- [ ] Tagged v1.0 release with docs, demo dataset, and walkthrough video.
- [ ] Video demonstrates: market data → strategy signals → risk → fills → P&L → replay → RCA.

#### Exit Criteria
- [ ] Tagged v1.0 release with docs, demo dataset, and short walkthrough video.
