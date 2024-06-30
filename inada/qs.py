import glob
import os


def main():
    for file in glob.glob('problems/spaceship/*.txt'):
        filename = os.path.basename(file)
        with open(file) as f:
            lines = [tuple(map(int, line.strip().split())) for line in f]

        lines.append((0, 0))
        points = sorted(set(lines))

        with open("inada/spaceship/" + filename[:-4] + ".qs", 'w') as f:
            f.write(f"{len(lines)} 0\n")
            for line in points:
                f.write(f"{' '.join(map(str, line))}\n")


if __name__ == '__main__':
    main()
