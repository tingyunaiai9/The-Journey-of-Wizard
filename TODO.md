# Bug：

- 武器攻击范围左右无法判断，当前是以shoot后再调整达成的

# Improvment：

- gameover界面的按钮有些不清楚
- 主菜单加其他按键，不能用fadeout的信号开始对战，改用按键对应的信号

- HP进度条变化比较粗糙，观察是以10hp跳一下，需要改为1hp
- 飞行攻击范围（AreaRect）过大，每种武器待调小，调准
- Hero攻击状态时，没有处理beHit，连续攻击是无敌的
- 更新 readme 中的单手剑类图的父类IWood
