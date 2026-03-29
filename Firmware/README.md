# Firmware

## Overview
STM32 firmware for LoRa to Modbus gateway and sensor nodes.

---

## Structure
- `gateway/` → Main gateway firmware (LoRa + Modbus)
- `node/` → Sensor node firmware
- `common/` → Shared code (protocols, utilities)

---

## Key Modules
- LoRa (SX1276 driver + packet parser)
- Modbus RTU (RS485 slave)
- Device management (data handling, stale logic)

---

## Build & Flash
1. Open in STM32CubeIDE
2. Build project
3. Flash using ST-Link

---

## Notes
- Keep protocol changes synced with `docs/`
- Do not change register mapping without approval