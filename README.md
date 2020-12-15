# cmsec
cpp micro service. c++ 微服务

## [中文文档](README_zh_cn.md)


# support list
- [grpc](https://github.com/grpc)
- [ipaddr](https://github.com/gmsec/micro/tree/master/example/main.go#80) It can be directly connected through IPaddr
- [go micro support](https://github.com/gmsec/gmsec)

# windows install

need list (cmake,make,msbuild,git)

- install [vs2019](https://visualstudio.microsoft.com/zh-hans/vs/community/)
- install [cmake](https://cmake.org/)
- install [git](https://git-scm.com/)
- install [mingw64](http://www.mingw.org/)
- shell execute [proto_install_windows_git_bash](proto_install_windows_git_bash.sh)
- done file in (output/grpc)

# linux install

```
sudo apt-get install build-essential autoconf libtool pkg-config
sudo apt-get install cmake
sudo apt-get install clang-5.0 libc++-dev
```
```
sudo ./proto_install_linux_cmake.sh
```
- done


more : https://github.com/grpc/grpc/blob/master/BUILDING.md