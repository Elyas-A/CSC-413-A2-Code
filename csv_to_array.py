import csv
file_path: str = './party_rock_anthem.csv'

with open(file_path, newline='') as csvfile:
    reader = csv.reader(csvfile)
    f = open('output.ino', 'w')
    f.write("int song_map [][1000] = {\n")
    for row in reader:
        if ' ' in row[0]:
            arrows = row[0].split(' ')
            f.write(f"    {{{arrows[0]}{arrows[1]}, {row[1]}, {row[2]}}},\n")
        else:
            if row[0] == '':
                row[0] = 0
                row[1] = 0
            f.write(f"    {{{row[0]}, {row[1]}, {row[2]}}},\n")
    f.write("};\n")
    f.close()