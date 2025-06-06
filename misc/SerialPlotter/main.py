from matplotlib.animation import FuncAnimation

from lib.SerialReader import SerialReader
from lib.Graphing import Graph
from lib.DataParser import DataParser

DEBUG = True
DELAY = 100 #ms

def main():
    spectrometerSerial = SerialReader("COM7", debug = DEBUG)
    sharedQueue = spectrometerSerial.getQueue()
    dataParser = DataParser(sharedQueue, debug = DEBUG)
    graph = Graph()

    spectrometerSerial.start()

    def update(frame):
        if DEBUG: print("Running update function.")
        data = dataParser.runInternalCycle()
        if data:
            graph.setData([range(len(data)),data])
            graph.updateGraph()
    

    animation = FuncAnimation(graph.figure, update, interval=DELAY, cache_frame_data=False)
    graph.openWindow(blocking=True)

    

if __name__ == "__main__":
    main()