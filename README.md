# flappyfpga

- **Course:** IS1500 – Computer Organization and Components (KTH)
- **Project Type:** Mini Project Assignment
- **Authors:** Eric Strihagen, Axel Öberg

---

## Project Overview

`flappyfpga` is a hardware implementation of a simple game inspired by *Flappy Bird*, designed to run on FPGA boards using the **RISC-V 32-bit (riscv32) instruction set**. The game leverages the DE10-Lite FPGA boards provided by KTH and demonstrates basic hardware-software co-design, input handling, and VGA output.

Players control a bird using the FPGA **buttons**, navigating through obstacles rendered on a **VGA display**.

---

## Hardware

- **FPGA Board:** Terasic DE10-Lite
- **Input:** Push buttons (for controlling the bird)
- **Output:** VGA display

---

## Software / Toolchain

- **Instruction Set:** RISC-V 32-bit (riscv32)
- **Toolchain:** KTH-provided RISC-V toolchain for compilation and programming

---

## Features

- Real-time VGA graphics output
- Button-controlled bird movement
- Obstacle generation and collision detection
- Score tracking (optional / future improvement)

---

## Getting Started

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/flappyfpga.git
   ```

2. Navigate to the project directory:
   ```bash
   cd flappyfpga
   ```

3. Build the project (**RISC-V cross-compiler must be installed**):
   ```bash
   make
   ```

4. Run the project (**De10-Lite required & toolchain must be installed**):
   ```bash
   dtekv-run build/flappyfpga.bin
   ```

---
