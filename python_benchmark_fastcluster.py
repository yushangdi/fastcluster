import sys

import fastcluster
import numpy as np
import pandas as pd
import time


ADDR = "~/datasets/"

def main(dataset, method, metric='euclidean', save = False):
	data_addr = ADDR + dataset + ".pbbs"
	data = pd.read_csv(data_addr,  sep = " ", header=None)
	print(data.head(1))
	start_time = time.time()
	Z = fastcluster.linkage(data, method=method, metric=metric, preserve_input=True)
	end_time = time.time()
	print(dataset, method + "-" + metric + "-dm-chain", np.sum(Z[:,2]), end_time-start_time)
	if(save):
		np.savetxt(dataset + "-" +  method + "-" + metric + "-vec-dendro.txt", Z)
	

def main_vector(dataset, method, metric, drop = False, save = False):
	data_addr = ADDR + dataset + ".pbbs"
	data = pd.read_csv(data_addr,  sep = " ", header=None)
	if drop:
		data = data.drop(len(data.columns)-1, axis = 1)
	print(data.head(1))
	start_time = time.time()
	Z = fastcluster.linkage_vector(data, method=method, metric=metric)
	end_time = time.time()
	print(dataset, method + "-" + metric + "-vec", np.sum(Z[:,2]), end_time-start_time)
	if(save):
		np.savetxt(dataset + "-" +  method + "-" + metric + "-vec-dendro.txt", Z)

def main_vector_nnchain(dataset, method, metric, drop = False, save = False):
	data_addr = ADDR + dataset + ".pbbs"
	data = pd.read_csv(data_addr,  sep = " ", header=None)
	if drop:
		data = data.drop(len(data.columns)-1, axis = 1)
	print(data.head(1))
	start_time = time.time()
	Z = fastcluster.linkage_vector_nnchain(data, method=method, metric=metric)
	end_time = time.time()
	print(dataset, method + "-" + metric + "-vec-chain", np.sum(Z[:,2]), end_time-start_time)
	if(save): 
		np.savetxt(dataset + "-" +  method + "-" + metric + "-vec-dendro.txt", Z)

if __name__ == "__main__":
	dataset = sys.argv[1]
	method = sys.argv[2]
	drop = sys.argv[3] == "1"
	if method not in ['complete', "average", "single", "ward", "all", "linear", "us"]:
		print("invalid method ", method)
	else:
		print("start")
		if method == "all":
			main(dataset, 'complete')
			main(dataset, "ward")
			main(dataset, "average")
			main(dataset, "average", "sqeuclidean")
			main_vector(dataset, "ward", "euclidean", drop)
			main_vector_nnchain(dataset, "ward", "euclidean", drop)
			main_vector_nnchain(dataset, "average", "sqeuclidean", drop)
		elif method == "linear":
			main_vector(dataset, "ward", "euclidean", drop)
			# main_vector_nnchain(dataset, "ward", "euclidean", drop)
			# main_vector_nnchain(dataset, "average", "sqeuclidean", drop)
		elif method == "us":
			main_vector_nnchain(dataset, "ward", "euclidean", drop)
			print()
			main_vector_nnchain(dataset, "average", "sqeuclidean", drop)
		else:
			main(dataset, method)