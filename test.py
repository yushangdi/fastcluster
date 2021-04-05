import fastcluster
import pandas as pd
import numpy as np

data = pd.read_csv("/Users/sy/Desktop/MIT/OPTICS/pbbs/linkage/completeLinkage/datasets/10D_UCI1_19K.pbbs",  sep = " ", header=None)
Z = fastcluster.linkage_vector_nnchain(data, method='ward', metric='euclidean')
print(np.sum(Z[:,2]))
# 801775.8658383356