# 程序设计实训2024大作业：带有元素反应系统的2D横板动作游戏


- [程序设计实训2024大作业：带有元素反应系统的2D横板动作游戏](#程序设计实训2024大作业带有元素反应系统的2d横板动作游戏)
  - [1 游戏介绍](#1-游戏介绍)
    - [1.1 游戏背景](#11-游戏背景)
    - [1.2 游戏设定](#12-游戏设定)
      - [1.2.1 角色状态](#121-角色状态)
      - [1.2.2 装备](#122-装备)
      - [1.2.3 近战武器](#123-近战武器)
      - [1.2.4 远程武器](#124-远程武器)
      - [1.2.5 平台](#125-平台)
  - [2 如何编译运行](#2-如何编译运行)
  - [3 操作介绍](#3-操作介绍)
    - [3.1 玩家 1](#31-玩家-1)
    - [3.2 玩家 2](#32-玩家-2)
    - [3.3 其他操作](#33-其他操作)
  - [4 设计思路](#4-设计思路)
  - [5 模块之间逻辑关系](#5-模块之间逻辑关系)
  - [6 程序运行流程](#6-程序运行流程)
  - [7 功能需求完成情况](#7-功能需求完成情况)
    - [7.1 需求点1：基本移动和生命值](#71-需求点1基本移动和生命值)
    - [7.2 需求点2：多种地形](#72-需求点2多种地形)
    - [7.3 需求点3：生命值系统](#73-需求点3生命值系统)
    - [7.4 需求点4：物品掉落](#74-需求点4物品掉落)
    - [7.5 需求点5：近战武器](#75-需求点5近战武器)
    - [7.6 需求点6：弓和箭](#76-需求点6弓和箭)
    - [7.7 需求点7：火属性](#77-需求点7火属性)
    - [7.8 需求点8：冰属性](#78-需求点8冰属性)
    - [7.9 需求点9：电属性](#79-需求点9电属性)
    - [7.10 需求点10：多种盔甲](#710-需求点10多种盔甲)
    - [7.11 用户体验](#711-用户体验)
    - [7.12 可选需求点1：对战AI](#712-可选需求点1对战ai)
    - [7.13 可选需求点2：局域网联机](#713-可选需求点2局域网联机)
  - [8 参考文献](#8-参考文献)


## 1 游戏介绍

### 1.1 游戏背景

### 1.2 游戏设定

#### 1.2.1 角色状态

| 图片 | 说明 |
| --- | --- |
| ![](doc/pic/121_character_body.png) | 无装备 |
| ![](doc/pic/121_character_initial.png) | 初始套装 |
| ![](doc/pic/121_character_hitting.png) | 受击 |
| ![](doc/pic/121_character_burning.png) | 着火 |
| ![](doc/pic/121_character_frozen.png) | 冰冻 |
| ![](doc/pic/121_character_electric_shock.png) | 触电 |

#### 1.2.2 装备

| 图片 | 说明 |
| --- | --- |
| ![](doc/pic/122_hat_black.png) | 普通帽子 |
| ![](doc/pic/122_hat_flamebreaker.png) | 火抗帽子 |
| ![](doc/pic/122_hat_icebreaker.png) | 冰抗帽子 |
| ![](doc/pic/122_hat_electrobreaker.png) | 电抗帽子 |
|  |  |
| ![](doc/pic/122_wizard_robe_black.png) | 普通巫师袍 |
| ![](doc/pic/122_wizard_robe_flamebreaker.png) | 火抗巫师袍 |
| ![](doc/pic/122_wizard_robe_icebreaker.png) | 冰抗巫师袍 |
| ![](doc/pic/122_wizard_robe_electrobreaker.png) | 电抗巫师袍 |
|  |  |
| ![](doc/pic/122_shoes_black.png) | 普通鞋子 |
| ![](doc/pic/122_shoes_flamebreaker.png) | 火抗鞋子 |
| ![](doc/pic/122_shoes_icebreaker.png) | 冰抗鞋子 |
| ![](doc/pic/122_shoes_electrobreaker.png) | 电抗鞋子 |

#### 1.2.3 近战武器

| 图片 | 说明 | 图片 | 说明 |
| --- | --- | --- | --- |
| ![](doc/pic/123_单手剑_木质_普通.png) | 单手剑_木质_普通 | ![](doc/pic/123_单手剑_金属质_普通.png) | 单手剑_金属质_普通 |
| ![](doc/pic/123_单手剑_木质_火.png) | 单手剑_木质_火 | ![](doc/pic/123_单手剑_金属质_火.png) | 单手剑_金属质_火 |
| ![](doc/pic/123_单手剑_木质_冰.png) | 单手剑_木质_冰 | ![](doc/pic/123_单手剑_金属质_冰.png) | 单手剑_金属质_冰 |
| ![](doc/pic/123_单手剑_木质_电.png) | 单手剑_木质_电 | ![](doc/pic/123_单手剑_金属质_电.png) | 单手剑_金属质_电 |
|  |  |  |  |
| ![](doc/pic/123_双手剑_木质_普通.png) | 双手剑_木质_普通 | ![](doc/pic/123_双手剑_金属质_普通.png) | 双手剑_金属质_普通 |
| ![](doc/pic/123_双手剑_木质_火.png) | 双手剑_木质_火 | ![](doc/pic/123_双手剑_金属质_火.png) | 双手剑_金属质_火 |
| ![](doc/pic/123_双手剑_木质_冰.png) | 双手剑_木质_冰 | ![](doc/pic/123_双手剑_金属质_冰.png) | 双手剑_金属质_冰 |
| ![](doc/pic/123_双手剑_木质_电.png) | 双手剑_木质_电 | ![](doc/pic/123_双手剑_金属质_电.png) | 双手剑_金属质_电 |
|  |  |  |  |
| ![](doc/pic/123_长矛_木质_普通.png) | 长矛_木质_普通 | ![](doc/pic/123_长矛_金属质_普通.png) | 长矛_金属质_普通 |
| ![](doc/pic/123_长矛_木质_火.png) | 长矛_木质_火 | ![](doc/pic/123_长矛_金属质_火.png) | 长矛_金属质_火 |
| ![](doc/pic/123_长矛_木质_冰.png) | 长矛_木质_冰 | ![](doc/pic/123_长矛_金属质_冰.png) | 长矛_金属质_冰 |
| ![](doc/pic/123_长矛_木质_电.png) | 长矛_木质_电 | ![](doc/pic/123_长矛_金属质_电.png) | 长矛_金属质_电 |

#### 1.2.4 远程武器

| 图片 | 说明 | 图片 | 说明 |
| --- | --- | --- | --- |
| ![](doc/pic/124_初级法杖_木质.png) | 初级法杖_木质 | ![](doc/pic/124_初级法杖_金属质.png) | 初级法杖_金属质 |
| ![](doc/pic/124_连击法杖_木质.png) | 连击法杖_木质 | ![](doc/pic/124_连击法杖_金属质.png) | 连击法杖_金属质 |
| ![](doc/pic/124_群攻法杖_木质.png) | 群攻法杖_木质 | ![](doc/pic/124_群攻法杖_金属质.png) | 群攻法杖_金属质 |
|  |  |
| ![](doc/pic/124_能量球_普通.png) | 能量球_普通 |
| ![](doc/pic/124_能量球_火.png) | 能量球_火 |
| ![](doc/pic/124_能量球_冰.png) | 能量球_冰 |
| ![](doc/pic/124_能量球_电.png) | 能量球_电 |

#### 1.2.5 平台

| 图片 | 说明 |
| --- | --- |
| ![](doc/pic/125_地块_岩石.png) | 地块_岩石 |
| ![](doc/pic/125_地块_木质.png) | 地块_木质 |
| ![](doc/pic/125_地块_金属.png) | 地块_金属 |

注：以上大多数图片为本人制作

## 2 如何编译运行

本项目使用 `Qt Creator` 构建，
开发环境为：

    Win11
    Qt Creator 13.0.2
    Qt 6.8.0

运行：

    1. 在 Qt Creator 中选择 CMakeLists 打开项目
    2. 选择 Qt 6.8.0 MinGW 64-bit 或其他构建套件进行配置
    3. 点击编译运行


## 3 操作介绍

### 3.1 玩家 1

`按键A`：向左移动

`按键D`：向右移动

`按键W`：跳跃

`按键J`：拾取

`按键K`：近战武器攻击 / 切换箭矢

`按键L`：远程武器攻击 / 扔出近战武器

`按键I`：切换武器

### 3.2 玩家 2

`按键Left`：向左移动

`按键Right`：向右移动

`按键Up`：跳跃

`按键Comma`：拾取

`按键Period`：近战武器攻击 / 切换箭矢

`按键Slash`：远程武器攻击 / 扔出近战武器

`按键Shift`：切换武器

### 3.3 其他操作

`按键Return`：打开作弊码输入框

## 4 设计思路

1. 充分使用面向对象编程的思想，对不同模块进行抽象与封装

2. 利用状态模式(State Pattern)实现玩家不同元素与行为之间的状态切换

## 5 模块之间逻辑关系

`MyGame` 继承自 `QMainWindow`，是游戏主页面

`Scene` 继承自 `QGraphicsScene`，是游戏战斗主页面。在其子类 `BattleScene` 中，处理场景内各 `Item` 的交互

`Item` 继承自 `QGraphicsItem`，主要处理物品的显示、位置与移动


游戏场景中各物品均为 `Item` 的子类，如下图所示

![](doc/pic/5_item_class.png)

而某一元素某一材质的物品又为其大类的子类，下图以单手剑类为例（省略金属质子类）

![](doc/pic/5_one_handed_sword.png)

`CItemFactory` 为 `Item` 工厂，处理各种物品的生成


`IState` 为玩家状态类，继承自 `QObject`，处理玩家的元素与行为状态。设计如下图所示

![](doc/pic/5_hero_state_class.png)

状态切换如下图所示： TODO：更新状态切换图

![](doc/pic/5_hero_state.png)


`Character` 为玩家类，处理玩家的相关操作，与其他类的关系如下图所示

![](doc/pic/5_character_class.png)


## 6 程序运行流程

程序主要依靠 90FPS 的 `BattleScene::update()` 推动运行，

另外添加了数个辅助的 `QTimer`

每次 `update` 中，处理以下流程：

1. 用户输入
2. 移动
3. 拾取
4. 射击
5. 攻击
6. Fps
7. 生命值进度条显示更新、判断

## 7 功能需求完成情况

### 7.1 需求点1：基本移动和生命值

- [x] 人物左右移动
- [x] 人物跳跃，能够跳到更高的平台上
- [x] 实现重力加速度
- [x] 两个玩家同屏对战

![](doc/pic/71_move.png)

### 7.2 需求点2：多种地形

- [x] 不同高度的平台
- [x] 不同材质的平台：岩石、木质、金属

![](doc/pic/72_platform.png)

### 7.3 需求点3：生命值系统

- [x] 每个玩家各有100点生命值，在上方血条显示

![](doc/pic/73_life.png)

- [x] 受到伤害会减少生命值。一方生命值 $\leq 0$ 时，进入死亡状态

![](doc/pic/73_dead.png)

### 7.4 需求点4：物品掉落

- [x] 物品从空中随机出现，按照重力规律下落

![](doc/pic/74_drop.png)

- [x] 玩家可捡起附近物品

![](doc/pic/74_pick.png)

- [x] 按下回车可调出作弊码窗口，使用作弊码生成指定物品，具体对应如下
  ```
  E - Electro, F - Flame, I - Ice
  1 - Wooden, 2 - Metal
  S - Spear, 1 - OneHandedSword, 2 - TwoHandedSword
  B - PrimaryBow, 3 - ComboBow, 4 - AOEBow
  A - Armor, L - Leg Shoes, H - Head Hat
  ```

![](doc/pic/74_cheat_code.png)

### 7.5 需求点5：近战武器

- [x] 能渲染玩家装备的武器，有攻击动画
- [x] 可进行攻击
- [x] 近战武器有多种类型：单手剑、双手剑、矛
- [x] 近战武器有两种材质：木质、金属质

![](doc/pic/75_melee_attack.jpg)

- [x] 可投掷近战武器，受重力作用，接触人或平台触发攻击并消失

![](doc/pic/75_melee_shoot.jpg)

### 7.6 需求点6：弓和箭

- [x] 同时拥有近战武器和弓(法杖)时，玩家可切换武器
- [x] 空中会掉落不同元素类型的箭(能量球)，拾取可增加弹容量。可在不同类型的能量球间切换，可以出射，受重力作用。

![](doc/pic/76_change_arrow.jpg)

- [x] 支持三种类型不同的法杖

      1. 初级法杖：射程近，发射1个能量球
      2. 连击法杖：射程远，发射3个能量球，水平速度各不相同
      3. 群攻法杖：射程远，发射3个能量球，初速度方向不同

      注：发射多个能量球时，优先当前选择元素，若不够，则由其他元素补充；如果玩家持有能量球不够，则将已有能量球全部发射

- [x] 法杖有两种材质：木质、金属质
- [x] 能够渲染飞行中的箭和投掷武器

![](doc/pic/76_bow_shoot.jpg)

### 7.7 需求点7：火属性

### 7.8 需求点8：冰属性

### 7.9 需求点9：电属性

### 7.10 需求点10：多种盔甲

### 7.11 用户体验

### 7.12 可选需求点1：对战AI

### 7.13 可选需求点2：局域网联机

## 8 参考文献

> [1] Qt Documentation [EB/OL]，https://doc.qt.io
