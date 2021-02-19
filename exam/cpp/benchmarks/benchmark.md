## Benchmark

We compared the performance of our binary search tree to the c++ standard library functions std::map and std::unordered_map with integer key and value, the performance metric we used is the time to find 100 randomly drawn keys. We expect that std::map will show a logarithmic time complexity in the size of the container N O(log_{2}{N}) while for std::unordered_map the time complexity is constant O(1). For the unbalanced bst we expect O(log_{2}{N}) on average but O(N) in the worst case (the tree is a linked list), finally for the balanced version of the bst we will always have a time complexity of O(log_{2}{N}. The followind graph shows the time to find 100 keys averaged over 10 measurements with increasing size of the container, the data is obtained by running the code `benchmark.cc` compiled with -O3 optimization

![container_comparison](./results/container_comparison.png)

The results are consistent with our expectations, the unordered_map shows an approximately constant behaviour and is the fastest container, while the other containers show a logatithmic behaviour, with the balanced bst faster than the unbalanced one.

We also compared double key types with int key types, we expect that the tree with double keys will take longer to find the same amount of keys, this is confirmed from the graph below, however we expected a bigger difference between the key types.

![key_comparison](./results/key_comparison.png)


To produce the same graphs on your machine you can run the `test.sh` script found in the benchmarks folder. The script will compile the `benchmark.cc` code with -O3 optimization, run it and will execute the python script `analisys.py` which will produce the graphs.