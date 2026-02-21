# GUI Dashboard

A working browser GUI for the live `VirtualMoneySystem` REST API (no mock data).

## Run

1. Start backend (`VirtualMoneySystem`) and note the port.
2. Serve GUI:

```bash
python -m http.server 9090 -d gui
```

3. Open `http://localhost:9090` and set **Base URL** to backend URL (e.g., `http://localhost:18080`).

## Supported live operations
- Health check
- Signup + login
- Create wallet
- Deposit / withdraw / balance
- Transfer
- FX conversion
