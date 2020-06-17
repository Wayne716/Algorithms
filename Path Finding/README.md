### Dijkstra /w set in STL
```
初始化所有点的距离为无限大，起始点距离为0
用Set存放pair<距离, 到达点>，插入<0,start>

当Set非空时，取出首元素为u，遍历邻接点v
  若路径距离小于最小距离则更新记录
    若有则删除Set中旧的到达点v的<距离, 到达点>
    Set中添加新的<距离, 到达点>
```

### Dijkstra /w priority_queue in STL
```
初始化所有点的距离为无限大，起始点距离为0
初始化bool数组visited
用priority_queue存放pair<距离, 到达点>，插入<0,start>

当priority_queue非空时，取出队首节点为u，遍历邻接点v
  若已访问则跳过，否则记录该点已访问
  若路径距离小于最小距离则更新记录
    priority_queue中添加新的<距离, 到达点>
```
