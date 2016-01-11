
#Chinese Edition   
#FP_ROUND Bug描述
CrossBridge没有完整实现LLVM的FP_ROUND(高精度类型数据转低精度类型数据)操作, 即代码通过CrossBridge编译后，高精度类型数据有可能不会按代码写得那样转成低精度类型，比如double类型可能不会转成float类型

#CrossBridge源代码

[代码地址v15.0.0.3](https://github.com/crossbridge-community/crossbridge/tree/v15.0.0.3) 


#环境搭建

##Windows的环境搭建

   * Windows需要下载Cygwin+CrossBridgeSDK

   	[SDK](http://sourceforge.net/projects/crossbridge-community/files/15.0.0/CrossBridge_15.0.0.3.zip/download)
    
	解压到**cygWinLocal**

   * 获取源代码
   
		git clone https://github.com/niluzhou1984/SimpleCrossbridgeBadCase.git localDirName

   * 用localDirName/cygwinInstallFix 下面的run.bat和 setup-x86.exe替换**cygwinLocal**下的同名文件

   * 运行里面的run.bat自动安装cygwin
   
	我们把路径cygwinLocal/sdk 称为**SDK_PATH** ,后面的配置文件将会用到这个路径

##Mac的环境搭建

* [Crossbridge Sdk下载](http://sourceforge.net/projects/crossbridge-community/files/15.0.0/CrossBridge_15.0.0.3.dmg/download)
(sdk中包括了编译到avm需要用到的编译工具 库和头文件) 
    
    解压到目录**CrossBridgeSDK**(同windows下的cygWinLocal目录，只是mac下不需要装cygwin,压缩包里只包含了crossbridge的sdk).

	我们把路径 CrossBridgeSDK/sdk 称为**SDK_PATH** ,后面的配置文件将会用到这个路径
	
* 获取源代码
		git clone https://github.com/niluzhou1984/SimpleCrossbridgeBadCase.git  localDirName
		
####其他软件包需求
   * 64位的jvm
   * make
   
##以下Windwos和Mac相同

* 修改localDirName目录下的**MakefileCfg.mk** 设置FLASCC为**SDK_PATH**，使得Makefile运行的时候能找到正确版本的gcc


##编译
	sh localDirName/build.sh
	


##运行分析

在localDirName下会生成两程序
* simpletest_crossbridge.exe： 经过CrossBridge编译后的结果
* simpletest_llvm.exe:  经过原生llvm-2.9编译后的结果
另外生成一个经过CrossBridge编译后的结果的编译中间文件：    
* simpletest.cpp.lto.1.as 这个文件是crossbridge编译过程中生成的Machine Instruction文件 

* 按照程序逻辑 正常输出结果为:   
        如果S==0, 那么tempff == f？ 为 1(true),  tempff2 == f？为 0(false)    
        如果S==1, 那么tempff == f？ 为 0(false),  tempff2 == f？为 1(true)
	
* 分别运行两个程序，**可以发现两个程序运行结果不一致**:    
        simpletest_llvm.exe为正常运行结果，simpletest_crossbridge.exe运行结果不正常  


* 问题分析: 文件simpletest.cpp.lto.1.as中    
```
	line 59: f2 = (f1 * f1)      //f1*f1所得f2是64位精度的    
	line 60: s1 = f2/*fround*/  //fround本应实现从高精度转到低精度的转换，而实际只是简单赋值，并没有实现转换
```

#English Edition

#Bug Description about FP_ROUND opcode 
CrossBridge does not realize the opcode of FP_ROUND (the operation for converting high-precision type down to low-precision type) in LLVM framework correctly, that means the program compiled from CrossBridge may not convert the high-precision type down to low-precision type as we wished, for example from double to float


#CrossBridge Source code

[CrossBridge v15.0.0.3](https://github.com/crossbridge-community/crossbridge/tree/v15.0.0.3) 

#Build Test Enviroment

##Build Test Enviroment For Windows

   * Install Cygwin + CrossBridge SDK For Windows

   	[SDK](http://sourceforge.net/projects/crossbridge-community/files/15.0.0/CrossBridge_15.0.0.3.zip/download) 

	Decompress SDK package to directory **cygWinLocal** 

   * Get Source Code of Test Case
  
		git clone https://github.com/niluzhou1984/SimpleCrossbridgeBadCase.git localDirName

   * Replace **run.bat** and **setup-x86.exe** under directory **cygwinLocal** with the files under directory localDirName/cygwinInstallFix which have same names
    
   * execute run.bat to install cygwin 
   
	And we will use symbol **SDK_PATH** to denote the path "cygwinLocal/sdk" in following descriptions.

##Build Test Enviroment For Mac

* [Download Crossbridge Sdk](http://sourceforge.net/projects/crossbridge-community/files/15.0.0/CrossBridge_15.0.0.3.dmg/download)
    (All required Tools, libs and header files have been included in the sdk package)
	
    Decompress SDK package to directory **CrossBridgeSDK** (it's the corresponding directory cygWinLocal for mac, and we can skip the installation of cygwin, just simply decompress crossbridge SDK package to the directory).

	And we will use symbol **SDK_PATH** to denote the path "CrossBridgeSDK/sdk" in following descriptions.
	
* Get Source Code of Test Case For Mac 

		git clone https://github.com/niluzhou1984/SimpleCrossbridgeBadCase.git localDirName
		
####The Package Dependencies For Mac
   * 64-bit jvm
   * make
   
##The following steps can be applied to both Windows and Mac

* Modify **MakefileCfg.mk** under directory localDirName, set FLASCC=**SDK_PATH**, which can make us to find correct gcc while running Makefile

##Run

There will be two executable files(EXE) under directory localDirName:
* simpletest_crossbridge.exe：compiled from CrossBridge
* simpletest_llvm.exe: compiled from native unmodified llvm-2.9

there is one more intermediate file of machine instruction from CrossBridge：    
* simpletest.cpp.lto.1.as  


* According to test program, the correct output is:   
	if S==0, then tempff == f？ is 1(true),  tempff2 == f？is 0(false)    
	if S==1, then tempff == f？ is 0(false),  tempff2 == f？is 1(true)
	
* **But we can find that the outputs of two EXEs are inconsistent!**:    
       The output from simpletest_llvm.exe is correct， but the other one from simpletest_crossbridge.exe is incorrect!


* Problem Analysis  -----  in file simpletest.cpp.lto.1.as:    
```
	line 59: f2 = (f1 * f1)      //f1*f1, so f2 is 64-bit high-precision type     
	line 60: s1 = f2/*fround*/  //fround operation should convert high-precision type down to low-precision type, but here it is just a simple assignment 
```



