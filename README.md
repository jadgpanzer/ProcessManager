# ProcessManager
##简介
ProcessManager是一个用来控制进程的小程序，它拥有创建、停止、搜寻等基本功能
##运行环境
Windows64位系统
##使用方法
使用VScode生成项目即可运行，本程序依靠控制台启动，在启动时即提供参数:

    ProcessManager.exe [-option] [parameter]

可使用的option和parameter及其作用如下：

|Option|Parameter|Function|
|-|-|-|
|-c|Executable File Path|Create Process|
|-ki|Process ID|Kill Process(by PID)|
|-si|Porcess ID|Search Process(by PID)|
|-kn|Process Name|Kill Process(by Name)|
|-sn|Porcess ID|Search Process(by Name)|
|-e|None|Show All Process|

如果想重定向到文件，可以使用：
	
	ProcessManager.exe [-option] [parameter] > out.txt
