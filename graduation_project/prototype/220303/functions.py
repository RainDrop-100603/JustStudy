sound_label = 125

table1 = ("C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B")

sound = f"{table1[sound_label%12]}{sound_label/12}"
# A4 -> 57, C0~ G10

def make_output_label():
    