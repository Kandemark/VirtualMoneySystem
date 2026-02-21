import json
import urllib.request

class VirtualMoneyClient:
    def __init__(self, base_url: str):
        self.base_url = base_url.rstrip('/')

    def get_balance(self, wallet_id: str) -> dict:
        with urllib.request.urlopen(f"{self.base_url}/api/v1/wallets/{wallet_id}/balance", timeout=10) as resp:
            return json.loads(resp.read().decode("utf-8"))
