import stapipy as st
import os

try:
    st.initialize()
    sys = st.create_system()
    devices = sys.detect()
    print(f"Detected {len(devices)} devices")
    for i, d in enumerate(devices):
        print(f"Device {i}:")
        print(f"  Display Name: {d.display_name}")
        print(f"  Model:        {d.model}")
        print(f"  Serial:       {d.serial_number}")
        print(f"  IP:           {d.ip_address if hasattr(d, 'ip_address') else 'N/A'}")
except Exception as e:
    print(f"Error: {e}")
finally:
    st.terminate()
