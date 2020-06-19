### Dijkstra /w set in STL
```
初始化所有点的距离为无限大，起始点距离为0
用set存放pair<距离,到达点>，插入<0,start>

当set非空时，取出首元素为u，遍历邻接点v
  若路径距离小于最小距离则更新记录
    若有则删除set中旧的到达点v的<距离,到达点>
    set中添加新的<距离,到达点>
    
时间复杂度: O(|V+E|*log|V|)
```

### Dijkstra /w priority_queue in STL
```
初始化所有点的距离为无限大，起始点距离为0
初始化bool数组visited，默认为false
用priority_queue存放pair<距离,到达点>，插入<0,start>

当priority_queue非空时，取出队首节点为u，遍历邻接点v
  若已访问则跳过，否则记录该点已访问
  若路径距离小于最小距离则更新记录
    priority_queue中添加新的<距离,到达点>
    
时间复杂度: O(|V+E|*log|V|)
```

### Dijkstra in matrix
```
从起始点开始遍历所有的点，更新距离，标记起始点已访问。
从上一个已访问的点开始遍历所有的点直到访问所有的节点。

时间复杂度：O(|V|*|V|)
```
