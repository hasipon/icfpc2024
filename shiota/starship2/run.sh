for i in {25..25}; do
  echo "$i";
    echo -n "solve spaceship$i "  > $i.out
    ./a.out < ../../problems/spaceship/$i.txt  >> $i.out
    echo ""
  echo "$i";
done
