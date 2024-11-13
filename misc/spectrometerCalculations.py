class DataRateCalculations:
    def __init__(self):
        self.pixelCount       = 2048
        self.bitsPerPixel     = 16
        self.samplesPerSecond = 8

    def calculateBitsPerSecond(self):
        return self.pixelCount * self.samplesPerSecond * self.bitsPerPixel

    def calculateBytesPerMinute(self):
        return ((self.calculateBitsPerSecond() * 60) / 8) / 10 ** 6

class RotationCalculations:
    def __init__(self):
        self.hertz = 1

    def degreeOfRotationPerMilisecond(self):
        """
        returns the amount of degrees of rotation per milisecond given class' hertz rounded to 4 decimal places
        """
        return round((360 * self.hertz)/1000, 4)

class TimingCalculations:
    def __init__(self):
        self.totalMiliseconds = 1000 # One second
    
    def calculateSamplesPerSecond(self, times: list):
        """
        returns amount of samples per second rounded to the nearest 4 decimal places
        """
        return round(len(times)*(self.totalMiliseconds/sum(times)),4)

class SensitivityOffset:
    def __init__(self):
        self.MIN = 350
        self.MAX = 800
        self.SAMPLE_SIZE = 2048
     
    def calculateSensitivitySlope(self)
        pass

    


if __name__ == "__main__":
    # dataCalc = DataRateCalculations()
    # dataCalc.samplesPerSecond = 4
    # dataCalc.pixelCount = 1024
    # print("Total data with 16 bits:", dataCalc.calculateBytesPerMinute(), "MBpm")
    # dataCalc.bitsPerPixel = 8
    # print("Total data with  8 bits:", dataCalc.calculateBytesPerMinute(), "MBpm")

    # a = RotationCalculations()
    # print(f"Degree of rotation per mililsecond at {a.hertz}Hz is {a.degreeOfRotationPerMilisecond()}*")
    # a.hertz = 4.8
    # print(f"Degree of rotation per mililsecond at {a.hertz}Hz is {a.degreeOfRotationPerMilisecond()}*")

    b = TimingCalculations()
    print(b.calculateSamplesPerSecond([50,100,200]))
