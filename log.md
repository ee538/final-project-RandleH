# Log 项目问题日志

[EE538 Final Project] https://github.com/ee538/final-project-RandleH



## Xcode解除Hardened Runtime限制

`问题`: 开始运行直接进dylib not load错误

`解决`: 

打开 Project Nevigator

![image-20220402013514644](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013514644.png)

![image-20220402013526616](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013526616.png)

![image-20220402013629279](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013629279.png)



## Xcode 配置工作路径

`问题`:TrojanMap的CSV表格读取失败

`解决`:设置为项目工作路径的父级菜单而非默认的系统隐藏路径

![image-20220402012922551](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402012922551.png)

![image-20220402012850967](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402012850967.png)

![image-20220402012952972](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402012952972.png)

路径前加 “点”

![image-20220402014213431](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402014213431.png)



## Xcode 无视 Documentation Comments

`问题`: Warning太多

`解决`: 

打开 Project Nevigator

![image-20220402013922546](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013922546.png)

![image-20220402013934668](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013934668.png)

![image-20220402013944878](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402013944878.png)



## TrojanMap 读取CSV数据错误

`问题`: 

![image-20220402014647057](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402014647057.png)

该程序读取时包含了表头, 表头为英文单词字母无法转为数字导致异常

![image-20220402014740590](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402014740590.png)



`解决`: 

![image-20220402015613802](/Users/randle_h/Library/Application Support/typora-user-images/image-20220402015613802.png)

在进循环前先做一次`getline(fin, line);` 跳过表头. 即可正常读取坐标并绘制.

<img src="/Users/randle_h/Library/Application Support/typora-user-images/image-20220402015744758.png" alt="image-20220402015744758" style="zoom:30%;" />





## 排序算法与大小写敏感问题

大小写敏感会使得数组的排序相对位置发生改变.





## Autocomplete函数

判断目标字符串是否包含于列表中的地点名称, 不可简单地判断字符串是否为子串关系.

例如目标字符串`er` 和地点名称 `Department center`存在包含关系, 但不能作为Autocomplete的答案.







## 可优化项

```c++
int TrojanMap::CalculateEditDistance(std::string a, std::string b);
```

> ```c++
> int TrojanMap::CalculateEditDistance( const std::string& a, const std::string& b);
> ```
>
>  





```c++
std::vector<std::string> TrojanMap::Autocomplete(std::string name);
```

> ```c++
> std::vector<std::string> TrojanMap::Autocomplete(const std::string& name);
> ```
>
> 



