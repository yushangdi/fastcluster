# fastcluster

This is adapted from the fastcluster project: http://danifold.net/fastcluster.html


# Installation

* g++ &gt;= 7.5.0 
* python


```bash
python setup.py install # you might need sudo priviledge
```

# Run

```python
import fastcluster

"""
works for:
complete, euclidean
ward, euclidean
average, euclidean
average, sqeuclidean
""" 
Z = fastcluster.linkage(data, method=method, metric=metric, preserve_input=True)

"""
works for:
ward, euclidean
average, sqeuclidean ?
""" 
Z = fastcluster.linkage_vector(data, method=method, metric=metric)

"""
works for:
ward, euclidean
average, sqeuclidean
""" 
Z = fastcluster.linkage_vector_nnchain(data, method=method, metric=metric)
```