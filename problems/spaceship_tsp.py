import os
import sys

from python_tsp.heuristics import (
    solve_tsp_simulated_annealing,
    solve_tsp_local_search,
    solve_tsp_lin_kernighan,
    solve_tsp_record_to_record)
from python_tsp.distances.data_processing import process_input


def max_xy_distance(sources):
    return (abs(sources[:, :, None] - sources[:, :, None].T)).max(axis=1)


def save_tsp(f, points, permutation, distance):
    f.write(f"# distance={distance}\n")
    for i in range(len(permutation)):
        if i == 0:
            continue
        x, y = points[permutation[i]]
        f.write(f"{x} {y}\n")


def find_distance_memo(f):
    key = "# distance="
    for line in f:
        if line.startswith(key):
            return float(line[len(key):])


def solve_first_time(prob_no: int):
    prob_path = f"spaceship/{prob_no}.txt"
    out_path = f"spaceship_tsp/{prob_no}.txt"

    if os.path.isfile(out_path):
        return

    with open(prob_path) as f:
        points = [tuple(map(int, line.strip().split())) for line in f]

    points.insert(0, (0, 0))
    sources, _ = process_input(points)
    distance_matrix = max_xy_distance(sources)
    distance_matrix[:, 0] = 0
    print("solving", prob_no)
    # distance_matrix: np.ndarray,
    # x0: Optional[List[int]] = None,
    # perturbation_scheme: str = "two_opt",
    # alpha: float = 0.9,
    # max_processing_time: Optional[float] = None,
    # log_file: Optional[str] = None,
    # verbose: bool = False,
    permutation, distance = solve_tsp_simulated_annealing(
        distance_matrix,
        max_processing_time=60.0 * 5,
    )
    print("solved", prob_no, distance)

    with open(out_path, "w") as f:
        save_tsp(f, points, permutation, distance)


def improve(prob_no: int):
    tsp_path = f"spaceship_tsp/{prob_no}.txt"
    prev_distance = None
    with open(tsp_path) as f:
        points = [tuple(map(int, line.strip().split())) for line in f if not line.startswith("#")]

    with open(tsp_path) as f:
        prev_distance = find_distance_memo(f)

    if not prev_distance or not points:
        return

    print(f"start improving problem{prob_no} points={len(points)} distance={prev_distance}")
    points.insert(0, (0, 0))
    sources, _ = process_input(points)
    distance_matrix = max_xy_distance(sources)
    distance_matrix[:, 0] = 0
    permutation, distance = solve_tsp_lin_kernighan(
        distance_matrix,
        x0=[x for x in range(len(points))],
        #max_processing_time=60.0 * 5,
    )

    with open(tsp_path) as f:
        prev_distance = find_distance_memo(f)

    if distance < prev_distance:
        print(f"improved problem={prob_no} prev={prev_distance} distance={distance} improved={distance-prev_distance}")
        with open(tsp_path, "w") as f:
            save_tsp(f, points, permutation, distance)


def main():
    if 1 < len(sys.argv):
        improve(int(sys.argv[1]))
    else:
        for i in range(11, 26):
            improve(i)


if __name__ == "__main__":
    main()
