#!/usr/bin/env python3

import fastcluster
import pandas as pd
import numpy as np

# 10D_UCI1_19K.pbbs
data = pd.read_csv("~/pbbs/linkage/completeLinkage/datasets/10D_UCI4_100K.pbbs",  sep = " ", header=None)
# data = pd.read_csv("/Users/sy/Desktop/MIT/OPTICS/pbbs/linkage/completeLinkage/datasets/small/example2.pbbs",  sep = " ", header=None)
print("start")
# Z = fastcluster.linkage(data, method='average', metric='sqeuclidean')
# print(np.sum(Z[:,2]))
Z1 = fastcluster.linkage_vector_nnchain(data, method='average', metric='sqeuclidean')
print(np.sum(Z1[:,2]))
print()
# Z = fastcluster.linkage(data, method='ward', metric='euclidean')
# print(np.sum(Z[:,2]))
Z1 = fastcluster.linkage_vector_nnchain(data, method='ward', metric='euclidean')
print(np.sum(Z1[:,2]))
print()
# Z2 = fastcluster.linkage_vector(data, method='ward', metric='euclidean')
# print(np.sum(Z2[:,2]))



# Z2 = fastcluster.linkage(data, method='average', metric='sqeuclidean')
# print(np.sum(Z2[:,2]))

# print(Z[1:30,:])
# for i in range(len(Z1)):
#   if((Z1[i]!=Z2[i]).any()):
#     print(Z1[i])
#     print(Z2[i])
#     print("=====")
#     # break

# 801775.8658383356
# 438466.5295854653
# 20366870.402506985