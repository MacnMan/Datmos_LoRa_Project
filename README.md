# LoRa to Modbus Gateway

## Overview
STM32-based LoRa gateway using SX1276.  
Receives data from LoRa nodes and exposes it via Modbus RTU (RS485).

---

## Features
- LoRa (SX1276) packet reception  
- Modbus RTU slave interface  
- Multi-device support (10 devices)  
- RSSI, battery, timestamp, stale flag  
- Structured register mapping  

---

## Folder Structure
- `firmware/` → STM32 code  
- `hardware/` → PCB & schematics  
- `docs/` → protocol & register map  
- `testing/` → test cases & logs  
- `tools/` → utilities  

---

## Getting Started
1. Open project in STM32CubeIDE  
2. Build firmware  
3. Flash to STM32  
4. Connect RS485 + LoRa module  

---

## Modbus Mapping
Each device = 10 registers  
See: `docs/protocol/modbus_register_map.md`

---

## Team Workflow
- Tasks → Jira  
- Communication → Slack  
- Time tracking → Clockify  

---

## License
MIT