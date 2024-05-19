# PowerTCP Evaluation

[PowerTCP](https://github.com/inet-tub/ns3-datacenter) 的实验复现。

- `results_burst`：评估突发场景，拓扑用的是默认的拓扑，实验结果基本和论文里吻合。
- `results_fairness`：评估公平性场景，只有 HPCC 和 PowerTCP 收敛了，其他的都没有收敛，很奇怪。
- `analyze-workload.py`：算 P99 和 P999。

`workload` 的实验数据太多了，画不过来了。并且原来的 repo 里没有 Homa 实验代码，不太清楚怎么回事。

它会同时跑 38 个实验，并且每个实验都要占 1G 左右的内存，workload 跑一组实验最慢的要两小时，注意跑实验的服务器配置要高。

HeRaNO @ 2024.4.8
