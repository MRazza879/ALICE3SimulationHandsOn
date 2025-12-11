---
marp: true
theme: default
paginate: true
---

# Fast Analysis Tool (FAT)
## ALICE 3 Simulation Hands-On

Session 2 - 45 minutes

---

## Session Agenda

- **10 min** - Learn what FAT does
- **20 min** - Build your own detector layout & extract momentum resolution
- **15 min** - Learn how to produce LUTs

---

## What is FAT?

**Fast Analysis Tool** - A framework for:
- Quick detector performance studies
- Parametric simulations
- Momentum resolution extraction
- Look-Up Table (LUT) generation

---

## Why Use FAT?

- ⚡ **Fast** - No need for full simulation
- 🔧 **Flexible** - Easy to modify detector configurations
- 📊 **Analysis** - Direct performance metrics
- 🔄 **Integration** - Produces LUTs for FastSimulation

---

## FAT Workflow

```
Detector Geometry → FAT → Performance Metrics
                         ↓
                    LUT Generation
                         ↓
                  FastSimulation Input
```

---

## Part 1: Understanding FAT
### What does FAT do?

- Parametrizes detector response
- Calculates tracking resolution
- Generates smearing parameters
- Compares with ACTS full tracking

---

## Detector Layout

Key parameters:
- Layer positions (r, z)
- Material budget (X/X₀)
- Resolution (spatial, timing)
- Magnetic field

---

## Part 2: Hands-On Exercise
### Build Your Own Detector

**Task**: Create a detector layout and extract momentum resolution

**Steps**:
1. Define detector geometry
2. Run FAT simulation
3. Extract momentum resolution
4. Compare with ACTS output

---

## Momentum Resolution

**Key metric**: δpₜ/pₜ

- Measures tracking precision
- Function of momentum, η, and detector design
- Critical for physics performance

---

## Comparing FAT vs ACTS

- **FAT**: Parametric, fast
- **ACTS**: Full tracking, detailed

**Goal**: Validate FAT predictions against ACTS

---

## Part 3: LUT Generation
### Look-Up Tables

**Purpose**: 
- Store smearing parameters
- Used by FastSimulation
- Speed up full analysis chain

---

## LUT Contents

- Momentum resolution vs pₜ, η
- Impact parameter resolution
- PID performance
- Efficiency maps

---

## Producing LUTs

**Process**:
1. Run FAT with full parameter space
2. Generate resolution maps
3. Store in LUT format
4. Validate against full simulation

---

## LUT Integration

```
LUT → FastSimulation → Analysis
```

Enables:
- Quick detector optimization
- Large-scale physics studies
- Systematic variations

---

## Session Goals

By the end, you should be able to:
- ✅ Produce a detector geometry
- ✅ Assess its performance with FAT
- ✅ Generate LUTs for FastSimulation
- ✅ Compare FAT and ACTS results

---

## Resources

- Google Slides: [Link](https://docs.google.com/presentation/d/1U-D6RVjo77e6QhOdkUnQzyk-gH2Jilij9oTfpMopiLI/edit?usp=sharing)
- ALICE 3 Documentation
- FAT Repository

---

## Questions?

Let's get started with the hands-on exercises!

---

## Backup: Key Concepts

- **Smearing**: Adding resolution effects
- **Parametrization**: Simplified detector response
- **pₜ**: Transverse momentum
- **η**: Pseudorapidity
- **X/X₀**: Material budget (radiation length)

---

## Backup: Common Issues

- Geometry definition errors
- Material budget inconsistencies
- Resolution parameter tuning
- LUT format compatibility

