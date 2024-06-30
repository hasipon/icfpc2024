import glob
import os


def main():
    for file in glob.glob('problems/spaceship/*.txt'):
        filename = os.path.basename(file)
        with open(file) as f:
            points = [tuple(map(int, line.strip().split())) for line in f]

        with open("inada/spaceship/" + filename[:-4] + ".tsp", 'w') as f:
            f.write("NAME spaceship {filename}\n")
            f.write("TYPE: TSP\n")
            f.write(f"DIMENSION: {len(points) + 1}\n")
            f.write(f"EDGE_WEIGHT_TYPE: MAX_2D\n")
            f.write(f"NODE_COORD_SECTION\n")
            f.write(f"0 0 0\n") # start point
            for i, point in enumerate(points):
                f.write(f"{i+1} {point[0]} {point[1]}\n")
            f.write(f"EOF\n")


if __name__ == '__main__':
    main()
