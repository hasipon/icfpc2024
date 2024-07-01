import os
from python_tsp.heuristics import solve_tsp_simulated_annealing, solve_tsp_local_search
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
        key = "# distance="
        for line in f:
            if line.startswith(key):
                prev_distance = float(line[len(key):])

    if not prev_distance or not points:
        return

    print(prev_distance)
    print(points)
    print(len(points))
    points.insert(0, (0, 0))
    sources, _ = process_input(points)
    distance_matrix = max_xy_distance(sources)
    distance_matrix[:, 0] = 0
    permutation, distance = solve_tsp_local_search(
        distance_matrix,
        max_processing_time=60.0 * 5,
    )

    if distance < prev_distance:
        print("improved", prob_no, prev_distance, distance)

        with open(tsp_path, "w") as f:
            save_tsp(f, points, permutation, distance)


def main():
    for i in range(5, 6):
        improve(i)


if __name__ == "__main__":
    main()
