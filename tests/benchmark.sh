ARG=$(shuf -i -5000:5000 -n 100 | tr '\n' ' ')
ops=$(./push_swap $ARG | wc -l)
echo "100 nums → $ops ops"
[[ $ops -lt 700 ]] || echo "Benchmark target missed: $ops"
