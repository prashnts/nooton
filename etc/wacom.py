import asyncio
from bleak import BleakScanner, BleakClient


STYLUS_ADDR = "8CD9F5F4-218C-D720-007F-B0535A7CFFBF"
EVENT_UUID = "00001524-1212-EFDE-1523-785FEABCD123"

async def main():
    async with BleakClient(STYLUS_ADDR) as client:
        while True:
            event_b = await client.read_gatt_char(EVENT_UUID)
            print(event_b.hex())

asyncio.run(main())


# http://developer-docs.wacom.com/mobile-stylus/docs/bsf-overview
