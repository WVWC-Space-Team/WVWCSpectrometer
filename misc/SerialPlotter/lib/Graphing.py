import matplotlib.pyplot as plt

class Graph:
    def __init__(self):
        self.plotData = [[],[]] # x, y : NOTE : Must be same length
        plt.ion() # Enables interactive mode
        self.figure, self.graph = plt.subplots()
        self.line, = self.graph.plot(*self.plotData)
        self.figure.canvas.draw()
        self.figure.canvas.flush_events()
    
    def setData(self, newData: list[list[int], list[int]]) -> bool:
        if newData is None:
            return False
        
        if len(newData[0]) != len(newData[1]):
            return False
        
        self.plotData = newData
        return True
        
    def updateGraph(self) -> None:
        self.line.set_data(*self.plotData)
        self.graph.relim()
        self.graph.autoscale_view()
        self.figure.canvas.draw()

    def openWindow(self, blocking = False):
        plt.show(block=blocking)
