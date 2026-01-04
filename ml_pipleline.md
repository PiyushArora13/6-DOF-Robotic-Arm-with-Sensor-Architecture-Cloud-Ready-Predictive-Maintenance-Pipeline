# ML Pipeline Design – Predictive Maintenance for 6-DOF Robotic Arm

## Project Context
This document describes the **planned machine learning pipeline** for predictive maintenance of a 6-DOF robotic arm instrumented with vibration, temperature, and current sensors.

The robotic arm, motor control, and system architecture were successfully implemented and validated.  
However, due to unstable multi-sensor data acquisition and synchronization issues at the firmware level, the ML pipeline described here **was planned but not fully implemented**.

This document represents the **design intent and technical planning** of the ML system.

---

## 1. Objective

- Detect early signs of mechanical and electrical faults
- Enable condition-based and predictive maintenance
- Monitor joint-level and system-level health
- Reduce unexpected downtime and mechanical wear

---

## 2. Sensor Configuration

### Joint-Level Sensors (Each Vertex / Joint)
- Vibration sensor
- Temperature sensor

### System-Level Sensor
- Current sensor at main power source

**Rationale:**
- Joint-level vibration and temperature capture localized faults
- Centralized current sensing captures global load abnormalities

---

## 3. Planned Feature Engineering

### 3.1 Vibration Features (Per Joint)
- RMS vibration amplitude
- Peak-to-peak vibration
- Standard deviation
- Crest factor
- Frequency-domain energy (FFT bands)
- Spike/event count

**Fault Indicators:**
- Bearing wear
- Mechanical looseness
- Misalignment
- Structural resonance

---

### 3.2 Temperature Features (Per Joint)
- Absolute temperature
- Rate of temperature increase (ΔT/Δt)
- Temperature variance
- Joint-to-joint temperature differential

**Fault Indicators:**
- Motor overload
- Increased friction
- Cooling inefficiency

---

### 3.3 Current Features (System-Level)
- Average current draw
- Peak current
- Current ripple
- Startup inrush current
- Load-to-current correlation

**Fault Indicators:**
- Motor stalling
- Excessive load
- Power inefficiency

---

### 3.4 Feature Aggregation Strategy
- Sliding time windows (1s / 5s / 10s)
- Per-joint feature vectors
- Global system health vector

**Planned Feature Vector Example:**

---

## 4. Dataset Design

### 4.1 Dataset Structure
Each row represents sensor data aggregated over a fixed time window.

| Field Name | Type | Description |
|-----------|------|-------------|
| timestamp | datetime | Data capture time |
| joint_id | int | Joint index (1–6) |
| rms_vibration | float | RMS vibration |
| vibration_std | float | Vibration variability |
| peak_vibration | float | Maximum vibration |
| joint_temperature | float | Joint temperature |
| temperature_rate | float | Rate of temperature increase |
| avg_current | float | Average system current |
| peak_current | float | Peak system current |
| operating_mode | categorical | Idle / Motion / Load |
| health_label | categorical | Normal / Warning / Fault |

---

### 4.2 Labeling Strategy (Planned)
- Threshold-based rules
- Expert/manual annotation
- Deviation from baseline behavior

**Target Classes:**
- Normal
- Warning
- Critical Fault

---

### 4.3 Data Volume Targets
- Vibration sampling: 100–500 Hz
- Aggregation window: 1–5 seconds
- Expected dataset size: 50,000+ samples

---

### 4.4 Storage Strategy
- Edge buffering on ESP32 / SD card
- Cloud storage (CSV / Parquet)
- Dataset versioning for model iteration

---

## 5. Model Design

### 5.1 Problem Formulation
- Time-series classification
- Anomaly detection
- Fault prediction

---

### 5.2 Planned Models

#### Classical ML (Baseline)
- Random Forest
- XGBoost
- Support Vector Machine

**Input:** Engineered feature vectors  
**Output:** Health classification

---

#### Time-Series Models
- LSTM
- GRU
- Temporal CNN

**Input:** Sequential sensor windows  
**Output:** Fault probability

---

#### Unsupervised Models
- Isolation Forest
- Autoencoders
- One-Class SVM

**Purpose:** Detect unknown or unseen fault patterns

---

## 6. Training & Evaluation Plan

### Training Strategy
- Per-joint model training
- Global system-level model
- Time-aware cross-validation

### Evaluation Metrics
- Precision / Recall
- F1-score
- ROC-AUC
- False alarm rate
- Detection latency

---

## 7. Deployment Strategy (Planned)

- Edge-level threshold checks (ESP32)
- Cloud-based ML inference
- Dashboard visualization of arm health
- Control actions:
  - Normal
  - Warning
  - Emergency stop (kill)

---

## 8. Implementation Status Summary

| Component | Status |
|---------|--------|
| Feature design | Planned |
| Dataset schema | Planned |
| Model architecture | Planned |
| Data acquisition | Not achieved |
| Model training | Not implemented |
| Deployment | Not implemented |

---

## 9. Key Learnings

- Reliable sensor synchronization is critical
- Multi-sensor data acquisition needs dedicated timing control
- ML readiness depends more on data quality than model complexity
- Edge + cloud ML requires robust buffering and fault tolerance

---

## 10. Future Work

- Dedicated sensor acquisition MCU
- RTOS-based scheduling
- CAN / RS485 sensor bus
- Edge ML inference
- Real-world fault dataset creation

