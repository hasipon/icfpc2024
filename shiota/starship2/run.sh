for i in {23..23}; do
  echo "$i";
    echo -n "solve spaceship$i "  > $i.out
    ./a.out < ../../problems/spaceship/$i.txt  >> $i.out
    echo ""
done
