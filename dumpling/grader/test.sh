for f in ../data/*.in; do
    echo $f
    ./$1 < $f | tail -n 5
done
