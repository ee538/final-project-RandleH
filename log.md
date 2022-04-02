# Log 项目问题日志

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