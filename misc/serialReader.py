import serial
import time
from datetime import datetime

PORT = 'COM7'
BAUDRATE = 115200

def save_to_file(data_str):
    print("Captured Data Block:")
    print(data_str)
    print("-" * 40)
    
    timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
    filename = f"./output/{timestamp}.txt"
    with open(filename, 'w') as f:
        f.write(data_str)
    print(f"Saved data to {filename}\n")

buffer = ""

while True:
    try:
        with serial.Serial(PORT, BAUDRATE, timeout=0.5) as ser:
            print(f"Connected to {PORT}")
            while True:
                chunk = ser.read(ser.in_waiting or 1).decode('utf-8', errors='ignore')
                if chunk:
                    buffer += chunk
                    # Look for HEADER and FOOTER
                    while True:
                        start_idx = buffer.find("HEADER:")
                        end_idx = buffer.find("FOOTER", start_idx)
                        if start_idx != -1 and end_idx != -1:
                            # Extract full data block including HEADER and FOOTER
                            data_block = buffer[start_idx:end_idx + len("FOOTER")]
                            save_to_file(data_block.strip())
                            # Remove extracted block from buffer
                            buffer = buffer[end_idx + len("FOOTER"):]
                        else:
                            break
    except serial.SerialException:
        print(f"Disconnected. Waiting to reconnect to {PORT}...")
        time.sleep(1)
