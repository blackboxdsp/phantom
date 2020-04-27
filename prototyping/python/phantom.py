#===============================================================================
from modules import buffer, display, phasor, point, sample, wavetable

#===============================================================================
def main():
    frequency = [i * 100 for i in range(1, 6)]
    rate = 44100
    time = 2.4

    output_size = int(rate * time)
    output = buffer.Buffer(output_size)
    output.print()

#===============================================================================
main()