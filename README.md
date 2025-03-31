This is a light version of [terrace](https://github.com/PASSIONLab/terrace), in order to adapt to the commands of hls. 
```
@inproceedings{PandeyWHB21,
  author    = {Prashant Pandey and
               Brian Wheatman and
               Helen Xu and
               Aydin Buluc},
  title     = {Terrace: A Hierarchical Graph Container for Skewed Dynamic Graphs},
  booktitle={Proceedings of the 2021 ACM international conference on Management of Data},
  year      = {2021},
}
```
Howerver, the structure is too hard to be synthesize. Therefore, only C simulation is timed. Here is the result:


dataset 1 16v 100e


dataset 2 64v 500e


dataset 3 128v 1000e


dataset 4 1024v 5000e


PR's max iters = 10



complie & run time
||cpu|c simulation|
| :----: | :----: | :----: |
|ds1 BFS|0m2.528s|0m6.095s|
|ds1 PR|0m2.646s| 0m6.033s|
|ds2 BFS|0m2.551s|0m6.140s|
|ds2 PR|0m2.660s|0m6.000s|
|ds3 BFS|0m3.299s0m6.895s|
|ds3 PR|0m3.239s|0m6.669s|
|ds4 BFS|0m3.206s|0m6.645s|
|ds4 PR| 0m3.187s| 0m6.657s|
