
# BLE Sensor Simulation Project
--

## 📚 About This Project

This project was developed by **Utku Enes Önmaz** as part of the Borda Academy Embedded Systems Developer Case.

The goal was to simulate a BLE-enabled embedded system that collects sensor data (temperature, humidity, CO₂), processes it, and broadcasts it in a meaningful and compact BLE advertisement packet.

As a student and developer, I approached this case as if I was building the base logic of a real-world IoT device, even without physical sensors. All data is simulated but the logic is real: from data collection and filtering, to buffer management and BLE packet encoding.

---
## ⚙️ How It Works
1. 📏 Collects 5 recent readings for each sensor (simulated)
2. 🧮 Calculates the **median** to smooth out sudden jumps
3. 🔁 Stores the medians in a circular buffer (like a small notepad)
4. 📊 Computes **stats** (median, min, max, std dev) over all recent values
5. 🎯 Converts each stat into a short 2-byte format (BLE likes things small)
6. 📡 Packs them into a BLE advertisement packet
7. 🔁 Repeats every 30 seconds

The system runs on a Linux machine with Bluetooth tools (`hcitool`, `hciconfig`), and you can monitor the broadcast using apps like **LightBlue** on your phone.

---
---

## 🗂️ Extra Files

- 📄 `output.txt`  
  Sample console output of the program during runtime.  
  Includes sensor readings, calculated stats, and BLE payload logs.

- 🧩 `Borda_Chart.pdf`  
  Visual chart of the system architecture.  


These files are included in the repository to help understand how the system works internally and how it communicates over BLE.


This project helped me understand how embedded systems manage real-time data, how buffers and encoding work, and how even limited BLE packets can carry rich information if structured wisely.
