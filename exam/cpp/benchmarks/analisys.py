import numpy as np
import pylab as pl

files = ["map_int", "u_map_int", "bst_int", "bst_int_b"]
labels = ["map", "unordered map", "bst", "balanced bst"]
colors = ["tab:cyan", "tab:orange", "tab:green", "tab:purple"]
N = np.loadtxt("results/map_int.txt")[:, 0]

for f, l, c in zip(files, labels, colors):
    line = np.loadtxt("results/"+f+".txt")[:, 1] / 1000
    pl.plot(N, line, label=l, color=c)

pl.xlabel("container size")
pl.ylabel("time to find 100 keys[ms]")
pl.title("int key type")
pl.legend()
pl.savefig("timing_int.png")
pl.show()


files = ["bst_int", "bst_int_b"]
labels = ["bst", "balanced bst"]
colors = ["tab:green", "tab:purple"]

for f, l, c in zip(files, labels, colors):
    line = np.loadtxt("results/"+f+".txt")[:, 1] / 1000
    pl.plot(N, line, label=l+" int", color=c)

    f = "results/"+f.replace("int", "double")+".txt"
    line = np.loadtxt(f)[:, 1:] / 1000
    pl.plot(N, line, "--", label=l+" double", color=c)

pl.xlabel("container size")
pl.ylabel("time to find 100 keys[ms]")
pl.title("int and double key type")
pl.legend()
pl.savefig("timing_double.png")
pl.show()