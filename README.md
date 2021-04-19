# A-Search-Algorithm
A* Search Alogrithm demostrating with UI interface
<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/sqrt(xxplusyy).png" width="640" height="640">
</p>

# (0)Environment
- Win10 X64
- CodeBlocks
- opencv(just few steps to config CodeBlocks with opencv,following [Link](https://blog.csdn.net/libizhide/article/details/108417216?spm=1001.2014.3001.5501))

# (1)Game rules
- Moving from lower right conner block to upper left corner block.Try to find the smallest steps path, and you are allowed to move to one of the 8 near blocks by one step.Caution! Avoid the gray blocks.

# (2)A* Search Alogrithm
- Visit [Site](https://en.wikipedia.org/wiki/A*_search_algorithm).
- Anyway, A* Search Alogrithm obtains completeness, optimality, and optimal efficiency.

# (3)Heuristic Fuction
Adjust different heuristic functions to approach various search algorithm
- <img src="https://render.githubusercontent.com/render/math?math=h(n)=\sqrt{x_n^2%2By_n^2}">：

<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/sqrt(xxplusyy).png" width="320" height="320">
</p>

- <img src="https://render.githubusercontent.com/render/math?math=h(n)=|x_n|%2B|y_n|">：

<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/abs(x)plusabs(y).png" width="320" height="320">
</p>

- <img src="https://render.githubusercontent.com/render/math?math=h(n)=|x_n-y_n|">(An interesting search 2333)：

<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/x-y.png" width="320" height="320">
</p>

- <img src="https://render.githubusercontent.com/render/math?math=h(n)=\sqrt{x_n^2%2By_n^2}*1000">(Hight weight of heuristic function,similar to Greedy Search Algorithm)：

<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/sqrt(xxplusyy)1000.png" width="320" height="320">
</p>

- <img src="https://render.githubusercontent.com/render/math?math=h(n)=\sqrt{x_n^2%2By_n^2}/1000">(Low weight of heuristic function,similar to Brute Force Search Algorithm)：

<p align="center">
  <img src="https://github.com/bizhili/A-Search-Alogrithm/blob/main/pic/sqrt(xxplusyy)divide1000.png" width="320" height="320">
</p>

# (4)Next step
Not planed




