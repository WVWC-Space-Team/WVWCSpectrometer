from queue import Queue
from datetime import datetime

class DataParser:
    def __init__(self, queue: Queue, outputFolder: str = "./output/", debug = False):
        self.queue = queue
        self.outputFolder = outputFolder
        self.debug = debug

        self.header = b'ZEKE'
        self.footer = b'JESS'
        
        self.buffer     = bytearray()
        self.rawPayload = []
        self.payload    = []

    def runInternalCycle(self) -> bool | list:
        if not self.readQueue():
            return False

        # self.saveBufferToFile()
        
        if not self.parseBuffer():
            return False
        
        self.convertData()
        return self.getPayload()


    def readQueue(self) -> bool:
        if not self.queue.empty():
            self.buffer.extend(self.queue.get())
            if self.debug: print(f"Buffer was extended to {len(self.buffer)} bytes.")
            return True
        return False

    def parseBuffer(self) -> bool:
        headerIndex = self.buffer.find(self.header)
        if headerIndex == -1:
            if len(self.buffer) > 8192:
                del self.buffer[:-4096]
            return False

        if len(self.buffer) < headerIndex + len(self.header) + len(self.footer):
            return False
        
        footerIndex = self.buffer.find(self.footer, headerIndex + len(self.header))
        if footerIndex == -1:
            return False

        payloadStart = headerIndex + len(self.header)
        payloadEnd   = footerIndex
        self.rawPayload = self.buffer[payloadStart:payloadEnd]
        if self.debug: print(f"Raw payload start is {self.rawPayload[:5]}")

        del self.buffer[:footerIndex+len(self.footer)]

        return True
    
    def convertData(self) -> bool:
        """
        WARNING: This will clearn the current payload.
        """
        if not self.rawPayload:
            return False
        self.payload = [] # Clears current payload
        for i in range(0, len(self.rawPayload), 2):
            self.payload.append(int.from_bytes(self.rawPayload[i:i+2], 'little')) # Ensure it's little endian

    def getPayload(self) -> list[int]:
        return list(self.payload)
    
    def saveBufferToFile(self, filename: str = "") -> bool:
        if not filename:
            filename = self.outputFolder + datetime.now().strftime("%Y%m%d_%H%M%S") + ".bin"
        if len(self.buffer) == 0:
            return False
        
        with open(filename, 'wb') as file:
            file.write(self.buffer)