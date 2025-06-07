import serial
import queue
import threading
import time

class SerialReader:
    def __init__(self, port: str, baudrate: int = 115200, debug = False):
        self.debug   = debug
        self.serialPort = serial.Serial(port, baudrate, timeout = 0)
        if self.debug:
            if self.serialPort.is_open:
                print(f"Succesfully connected to {port}.")
        
        self.running = True
        self.queue   = queue.Queue()
        self.thread  = threading.Thread(target=self._serial_read_loop, daemon=True)
    
    def _serial_read_loop(self) -> None:
        if self.debug:
            print(f"Opened thread for listening to {self.serialPort.port}.")

        tempBuffer = bytearray()
        while self.running:
            if self.serialPort.in_waiting: # in_waiting returns the number of bytes currently in the input buffer
                data = self.serialPort.read(self.serialPort.in_waiting) # Reads all current data in queue
                tempBuffer.extend(data)

            if len(tempBuffer) > 4096:
                self.queue.put(tempBuffer[:]) # Puts the new data in the queue to be processed by other threads
                tempBuffer.clear()
            
            time.sleep(0.01) # Not to stress the CPU too much with this thread since the queue will fill up anyway
    
    def getQueue(self):
        return self.queue

    def start(self) -> None:
        self.thread.start()
    
    def stop(self) -> None:
        self.running = False
        self.thread.join()
        self.serialPort.close()
