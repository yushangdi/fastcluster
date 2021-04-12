#!/usr/bin/env bash

# for i in {1..3}; do  python3 python_benchmark_fastcluster.py 10D_UCI1_19K us 0 echo "\n"; done


python3 python_benchmark_fastcluster.py 2D_UniformFill_1M us 0 

python3 python_benchmark_fastcluster.py 2D_VisualVar_1M us 1

python3 python_benchmark_fastcluster.py 5D_UniformFill_1M us 1

python3 python_benchmark_fastcluster.py 5D_VisualVar_1M us 1

python3 python_benchmark_fastcluster.py HT us 1