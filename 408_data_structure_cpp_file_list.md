# 408 考研数据结构 C++ 文件清单

> 建议：一个相对独立的数据结构或核心算法主题对应一个 `.cpp` 文件。\
> 这些文件用于自己动手实现、复习和理解 408
> 数据结构，不追求工程级封装，也不必把每一道习题单独建成文件。

## 01 线性表（Linear List）

  英文文件名                   中文内容
  ---------------------------- ----------
  `sequential_list.cpp`        顺序表
  `singly_linked_list.cpp`     单链表
  `doubly_linked_list.cpp`     双链表
  `circular_linked_list.cpp`   循环链表
  `static_linked_list.cpp`     静态链表

## 02 栈、队列和数组（Stack, Queue and Array）

  英文文件名                 中文内容
  -------------------------- ----------------------------------
  `stack.cpp`                栈
  `shared_stack.cpp`         共享栈
  `queue.cpp`                队列
  `circular_queue.cpp`       循环队列
  `linked_queue.cpp`         链式队列
  `matrix_compression.cpp`   矩阵压缩存储、特殊矩阵与稀疏矩阵

> 栈在括号匹配、表达式求值、递归等问题中的应用，可以直接在 `stack.cpp`
> 中继续练习，不必为了每一种应用拆很多文件。

## 03 串（String）

  英文文件名              中文内容
  ----------------------- -----------------------------------
  `string_matching.cpp`   串的模式匹配（朴素匹配）
  `kmp.cpp`               KMP 模式匹配算法与 next / nextval

## 04 树与二叉树（Tree and Binary Tree）

  英文文件名                     中文内容
  ------------------------------ --------------------------------------------------
  `binary_tree.cpp`              二叉树：前序、中序、后序、层序遍历及基本递归操作
  `threaded_binary_tree.cpp`     线索二叉树
  `tree.cpp`                     一般树：双亲表示法、孩子表示法、孩子兄弟表示法
  `tree_forest_conversion.cpp`   树、森林与二叉树之间的转换
  `huffman_tree.cpp`             哈夫曼树与哈夫曼编码
  `disjoint_set.cpp`             并查集

> `binary_tree.cpp`
> 是这一章最重要的基础文件之一。求树高、结点数、叶子数、交换左右子树等递归算法都可以继续写在这个文件中。

## 05 图（Graph）

  英文文件名                    中文内容
  ----------------------------- --------------------------------
  `adjacency_matrix.cpp`        图的邻接矩阵存储
  `adjacency_list.cpp`          图的邻接表存储
  `graph_traversal.cpp`         图的 BFS 与 DFS 遍历
  `minimum_spanning_tree.cpp`   最小生成树：Prim、Kruskal
  `shortest_path.cpp`           最短路径：BFS、Dijkstra、Floyd
  `topological_sort.cpp`        拓扑排序
  `critical_path.cpp`           关键路径

> BFS、DFS 可以放在同一个 `graph_traversal.cpp` 中；Prim 和 Kruskal
> 也放在同一个最小生成树文件中，避免文件过度碎片化。

## 06 查找（Searching）

  英文文件名                 中文内容
  -------------------------- --------------------------------
  `sequential_search.cpp`    顺序查找
  `binary_search.cpp`        折半查找
  `binary_search_tree.cpp`   二叉排序树 / 二叉搜索树（BST）
  `avl_tree.cpp`             平衡二叉树（AVL）
  `red_black_tree.cpp`       红黑树
  `b_tree.cpp`               B 树
  `b_plus_tree.cpp`          B+ 树
  `hash_table.cpp`           散列表 / 哈希表

> 红黑树、B 树、B+ 树在 408
> 中更重要的是理解结构性质、查找过程以及插入删除规则。可以建立文件用于尝试实现，但不必因为完整代码很长而影响考研主线。

## 07 排序（Sorting）

  英文文件名             中文内容
  ---------------------- --------------------------------------
  `insertion_sort.cpp`   直接插入排序、折半插入排序
  `shell_sort.cpp`       希尔排序
  `bubble_sort.cpp`      冒泡排序
  `quick_sort.cpp`       快速排序
  `selection_sort.cpp`   简单选择排序
  `heap_sort.cpp`        堆排序
  `merge_sort.cpp`       归并排序
  `radix_sort.cpp`       基数排序
  `external_sort.cpp`    外部排序、败者树、多路归并等核心思想

## 推荐目录结构

``` text
408_Data_Structure/
│
├── 01_linear_list/
│   ├── sequential_list.cpp
│   ├── singly_linked_list.cpp
│   ├── doubly_linked_list.cpp
│   ├── circular_linked_list.cpp
│   └── static_linked_list.cpp
│
├── 02_stack_queue_array/
│   ├── stack.cpp
│   ├── shared_stack.cpp
│   ├── queue.cpp
│   ├── circular_queue.cpp
│   ├── linked_queue.cpp
│   └── matrix_compression.cpp
│
├── 03_string/
│   ├── string_matching.cpp
│   └── kmp.cpp
│
├── 04_tree/
│   ├── binary_tree.cpp
│   ├── threaded_binary_tree.cpp
│   ├── tree.cpp
│   ├── tree_forest_conversion.cpp
│   ├── huffman_tree.cpp
│   └── disjoint_set.cpp
│
├── 05_graph/
│   ├── adjacency_matrix.cpp
│   ├── adjacency_list.cpp
│   ├── graph_traversal.cpp
│   ├── minimum_spanning_tree.cpp
│   ├── shortest_path.cpp
│   ├── topological_sort.cpp
│   └── critical_path.cpp
│
├── 06_search/
│   ├── sequential_search.cpp
│   ├── binary_search.cpp
│   ├── binary_search_tree.cpp
│   ├── avl_tree.cpp
│   ├── red_black_tree.cpp
│   ├── b_tree.cpp
│   ├── b_plus_tree.cpp
│   └── hash_table.cpp
│
└── 07_sort/
    ├── insertion_sort.cpp
    ├── shell_sort.cpp
    ├── bubble_sort.cpp
    ├── quick_sort.cpp
    ├── selection_sort.cpp
    ├── heap_sort.cpp
    ├── merge_sort.cpp
    ├── radix_sort.cpp
    └── external_sort.cpp
```

## 使用原则

1.  **文件不是任务清单。**
    学到对应知识点时再创建并自己实现，不需要现在一次性全部写完。
2.  **以理解 408 为目标。**
    不追求复杂工程封装，优先保证数据结构、指针变化和算法过程清晰。
3.  **同一主题不要拆得过碎。**
    例如二叉树的三种递归遍历、层序遍历、求高度等统一放进
    `binary_tree.cpp`。
4.  **重要结构尽量亲手实现。**
    顺序表、链表、栈、队列、二叉树、图遍历、BST、AVL、哈希和主要内部排序尤其值得自己写。
5.  **复杂结构允许"理解优先"。**
    红黑树、B/B+树、外部排序等如果完整实现明显挤占备考时间，以理解考试要求为先。
