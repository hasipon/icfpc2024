for i in {25..25}; do
    echo -n "solve spaceship$i "; ./a.out < ../../problems/spaceship/$i.txt
    echo ""
done
