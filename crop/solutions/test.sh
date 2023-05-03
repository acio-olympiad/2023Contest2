for i in {1..100000}; do
    python3 gen.py > /tmp/a.in
    if ! (./tunan-full < /tmp/a.in > /tmp/a.out && ./evan-sub3 < /tmp/a.in > /tmp/a2.out && diff /tmp/a.out /tmp/a2.out); then
        echo "WA"
        break
    else
        printf "AC $i\r"
    fi
done
