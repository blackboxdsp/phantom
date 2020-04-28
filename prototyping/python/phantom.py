#===============================================================================
import random

from modules import buffer, phasor, point, sample, wavetable

#===============================================================================
def write_wav_file(frequency, rate, time):
    num_samples = int(rate * time)
    output = buffer.Buffer(num_samples)
    
    table_size = 2048
    sinetable = wavetable.Wavetable(table_size)
    sinetable.fill_table()
    sinetable.set_phase_delta(frequency, rate)

    inflections = []
    inflection_count = 3
    for i in range(1, inflection_count + 1):
        phase = float(i / inflection_count)
        inflection = point.Point(phase, random.uniform(0.0, 1.0))
        inflections.append(inflection)

    for inflection in inflections:
        saw_phasor = phasor.Phasor([inflection])
    
        for i in range(output.buffer_size):
            value = sinetable.get_next_sample(saw_phasor)
            output.set_sample(i, value)

        output.normalize()
        output.export_wav(f"sounds/sine-{frequency}-{inflection.x:.1}-{inflection.y:.1}.wav", rate)

#===============================================================================
def main():
    rate = 44100
    time = 1.2

    base_frequency = 55
    num_octaves = 3
    frequencies = [base_frequency * (2 ** i) for i in range(num_octaves)]

    for frequency in frequencies:
        write_wav_file(frequency, rate, time)

    table_size = 2048
    sinetable = wavetable.Wavetable(table_size)
    sinetable.fill_table()
    sinetable.set_phase_delta(frequency, rate)

#===============================================================================
if __name__ == "__main__":
    main()