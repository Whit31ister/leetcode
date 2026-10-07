# Strings, Integers, Booleans, Lists, and Dictionaries
target_ip = "192.168.1.1"      # String
open_ports = [22, 80, 443]     # List
is_vulnerable = True           # Boolean

# Dictionary (Key-Value pairs - great for structuring data)
target_info = {
    "ip": target_ip,
    "os": "Linux",
    "ports": open_ports
}

print(f"Scanning target: {target_info['ip']}")