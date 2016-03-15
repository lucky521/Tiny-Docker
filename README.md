# Tiny-Docker
To build a tiny container like Docker using `namespaces` and `cgroups`.


## Virtual Environment
Isolate target process's running environment from Linux. 
要让容器中的进程自我感觉运行在一个独立的系统环境当中，
需要隔离的资源包括CPU资源、Memory资源、文件系统、磁盘资源、其他进程、系统用户组、网卡、端口。
并且需要通过映射的方式是容器中的进程能够以独立的名义去远程通信。


## Build Container
`lu-container-root`作为容器模拟环境的根目录。

`build_script.sh`是将容器环境中所需要的系统文件拷贝到容器目录中去。

`clean-sysfile.sh`清除这些系统文件，只保留该项目自己的文件。

## How to Run

Run the following commands.

```
$ git clone git@github.com:lucky521/Tiny-Docker.git
$ cd Tiny-Docker/
$ gcc lu-container.c -o docker
$ sh ./build_script.sh
$ sudo ./docker
```

Then you will be in container world. It is like another linux shell. But the environment is virtual.

## Test Environment

```
$ pwd
$ ls
$ ps -elf
$ top
$ tree
$ netstat -ano
$ free -m 

```
