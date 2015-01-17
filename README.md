# Agenda-Master
2014 SYSUSS Junior Practical Training
Agenda Master Illustration
=================================================================================
此文件夹内的代码为中山大学软件学院（SYSUSS）2014年的实训代码，设计的是一个基于Linux
命令行的会议议程管理系统，该系统提供用户登录（login），新用户注册（register），已注
册用户登陆后用户可以删除(delete)当前用户账户，查询(query)用户名单，也可以添加(add)、
删除(delete)、查询(query)系统中记录的会议安排等管理功能。
在这个案例中，利用了面向对象程序的设计和实现技术，按用户需求对整个程序框架进行设计和
实现，并逐步完成了基本和扩展功能。完成此项目能掌握在Linux环境下进行代码编写、程序调试和
测试的基本知识，初步了解面向对象编程的过程、设计模式的作用、UML图的含义，加强C++编
程能力等技能。
*小规模：Line of Code(1k,2k)。
使用方法：在Linux命令行中索引（cd）至代码文件夹中，输入make执行makefile中的编译指令
生成Final可执行文件，最后执行Final（./Final)。
知识技术：Linux 程序设计、C++11标准、面向对象编程、设计模式初探、交互测试、 UML 理解。
更多功能的实现：
【1】Agenda Storage IO以及Agenda Service的日志功能（最多5分）
     编写一个单例的LOG类，在Agenda服务运行的时候记录StorageIO和Service的操作以供错误
     追踪。
【2】Socket网络编程（最多50分）
     使用POSIX Socket API 或者 ACE Boost等第三方库实现一个Agenda网络服务器，进一步
     分离Service和UI，对外提供多用户支持。
【3】更友好的用户接口（最多10分）
     可以尝试实现更友好的Terminal UI 或者使用GTK+、QT、wxWidgets等库实现GUI。
Copyright reserved by WarpPrism(ZhouJihao)
2014-06-30-------2014-11-1
================================================================================
