qqclient 为客户端程序，QT编写，images文件夹中为图标文件。
qqserver 为服务端程序，需要oracle11g2，createtable.sql为sql创建用户与密码的SQL指令（用户名为0-255，默认密码为123456），直接make之后，会生成一个qqserverd，为启动程序，可以用qqserver启动（支持start，stop，status），默认端口号为8080。

已知问题：
	修改密码比较麻烦
	不能传送文件等多项功能缺失，仅可用于聊天
	