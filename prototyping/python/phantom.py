#===============================================================================
from modules import buffer, phasor, point, sample, wavetable

#===============================================================================
def write_wav_file(frequency, rate, time):
    num_samples = int(rate * time)
    output = buffer.Buffer(num_samples)
    
    table_size = 2048
    sinetable = wavetable.Wavetable(table_size)
    sinetable.fill_table()
    sinetable.set_phase_delta(frequency, rate)
    
    for i in range(output.buffer_size):
        output.set_sample(i, sinetable.get_next_sample())

    output.export_wav(f"sounds/sine-{frequency}.wav", rate)

#===============================================================================
def main():
    rate = 44100
    time = 2.4

    base_frequency = 55
    num_octaves = 5
    frequencies = [base_frequency * (2 ** i) for i in range(num_octaves)]

    for frequency in frequencies:
        write_wav_file(frequency, rate, time)

    table_size = 2048
    sinetable = wavetable.Wavetable(table_size)
    sinetable.fill_table()
    sinetable.set_phase_delta(frequency, rate)

#===============================================================================
main()