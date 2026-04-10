# ⚡ Alchemy Crack Engine

A high-performance, modular password cracking framework built in C++ with multithreading, rule-based mutation, and a terminal UI.

---

## 🚀 Overview

Alchemy Crack Engine is a lightweight, extensible password cracking tool designed for cybersecurity research, red team simulations, and performance engineering.

It combines:

* ⚡ Multithreaded CPU cracking
* 🧠 Rule-based password mutation
* 📊 Real-time metrics tracking
* 🖥️ Terminal UI (TUI dashboard)
* 🔌 GPU-ready architecture (CUDA/OpenCL integration planned)

---

## 🧠 Features

* **Offline Hash Cracking**

  * SHA256 support (extensible)
* **Multithreading Engine**

  * Utilizes all CPU cores
* **Rule-Based Wordlist Mutation**

  * Uppercase transforms
  * Leetspeak substitutions
  * Pattern-based extensions
* **Batch Processing Pipeline**

  * Designed for GPU acceleration
* **Terminal UI (ncurses)**

  * Live attack stats
  * Clean ASCII dashboard
* **Modular Architecture**

  * Easy to extend (GPU, distributed, protocols)

---

## 🏗️ Project Structure

```
alchemy-crack/
├── include/
├── src/
│   ├── core/
│   ├── engine/
│   ├── modules/
│   ├── gpu/
│   ├── ui/
├── build/
├── CMakeLists.txt
```

---

## ⚙️ Requirements

### Linux (Recommended)

* g++
* cmake
* OpenSSL
* ncurses

Install dependencies:

```bash
sudo apt update
sudo apt install build-essential cmake libssl-dev libncurses5-dev libncursesw5-dev
```

---

## 🛠️ Build

```bash
git clone https://github.com/YOUR_USERNAME/alchemy-crack.git
cd alchemy-crack

mkdir build
cd build
cmake ..
make
```

---

## ▶️ Usage

```bash
./alchemy-crack <hash> <wordlist>
```

### Example:

```bash
echo -n "password123" | sha256sum

./alchemy-crack <hash> /path/to/wordlist.txt
```

---

## 📊 Example Output

```
[*] Starting multithreaded brute force...

[+] Password found: password123
```

---

## 🧩 Roadmap

* [ ] CUDA GPU acceleration
* [ ] OpenCL support
* [ ] Distributed cracking (multi-node)
* [ ] Advanced rule engine (mask attacks)
* [ ] Online attack modules (SSH/HTTP)
* [ ] Config-based attack profiles

---

## ⚠️ Disclaimer

This tool is developed for **educational purposes, cybersecurity research, and authorized testing only**.

Do NOT use this tool on systems without proper authorization.

---

## 👤 Author

* Mr-Infect
* Cybersecurity / Red Team Engineering

---

## ⭐ Contribution

Feel free to fork, improve, and contribute.
