g++ -Ofast -std=c++20 main.cpp -o main

run_problem() {
  OUTPUT_FILE="$1"-shiota-"$2".out
  # OUTPUT_FILE="$1"-shiota-sorted-"$2".in
  echo "start $1";
    echo -n "solve spaceship$1 "  > "$OUTPUT_FILE"
    ./main "$PROBLEM_ID" < ../../problems/spaceship_tsp/"$1".txt  >> "$OUTPUT_FILE"
    echo ""
  echo "end $1";
}

PROBLEM_ID=$1
HASH=$(git rev-parse --short HEAD)

echo "$HASH"

if [ -z "$PROBLEM_ID" ]; then
  for i in {1..25}; do
    run_problem "$i" "$HASH"
  done
else
  run_problem "$PROBLEM_ID" "$HASH"
fi
