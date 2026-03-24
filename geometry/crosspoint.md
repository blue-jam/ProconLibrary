---
title: 直線，線分の交差判定，交点計算
documentation_of: //geometry/crosspoint.hpp
---

直線の交差判定については簡単である．ベクトルa，bで表される直線とベクトルc，dで表される直線が与えられたとき，cross(b - a, d - c)が0であれば，2つの直線は平行であるから，重なっていない限り交差はしない．

### 使用方法

#### intersection

直線，線分の交点計算．2直線が平行でないことが前提．

### 確認済み問題

- AOJ 1283(intersection)

### 参考

- [deq notes](http://www.deqnotes.net/)
