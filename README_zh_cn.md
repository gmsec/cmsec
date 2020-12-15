# cmsec
cpp micro service. c++ 微服务

[cmsec](https://github.com/gmsec/cmsec)


# 支持列表
- [grpc](https://github.com/grpc)
- [ipaddr](https://github.com/gmsec/micro/tree/master/example/main.go#80) It can be directly connected through IPaddr
- [go micro support](https://github.com/gmsec/gmsec)

# windows 安装

需要以下程序(cmake,make,msbuild,git)

- install [vs2019](https://visualstudio.microsoft.com/zh-hans/vs/community/)
- install [cmake](https://cmake.org/)
- install [git](https://git-scm.com/)
- install [mingw64](http://www.mingw.org/)
- git shell execute [proto_install_windows_git_bash.sh]([proto_install_windows_git_bash.sh](https://github.com/gmsec/cmsec/blob/master/proto_install_windows_git_bash.sh))
- 完成 生成目录在 (grpc/build_grpc/output/grpc)

# linux install

```
sudo apt-get install build-essential autoconf libtool pkg-config
sudo apt-get install cmake
sudo apt-get install clang-5.0 libc++-dev
```

[proto_install_linux_cmake.sh](https://github.com/gmsec/cmsec/blob/master/proto_install_linux_cmake.sh))
```
sudo ./proto_install_linux_cmake.sh
```
- 完成 生成目录在 (grpc/build_grpc/output/grpc)


- 注意链接顺序
  
```
grpc++
grpc++_reflection
grpc++_unsecure
grpc++_alts
grpc++_error_details
grpc
grpc_unsecure
grpc_plugin_support
grpcpp_channelz
gpr
absl_synchronization
absl_symbolize
absl_stacktrace
absl_debugging_internal
absl_base
absl_strings
absl_strings_internal
absl_time
absl_time_zone
absl_exponential_biased
absl_spinlock_wait
absl_log_severity
absl_raw_logging_internal
absl_throw_delegate
absl_malloc_internal
absl_bad_optional_access
absl_civil_time
absl_int128
absl_demangle_internal
absl_graphcycles_internal
absl_hashtablez_sampler
absl_city
absl_raw_hash_set
absl_str_format_internal
absl_cord
absl_status
absl_bad_variant_access
absl_hash
absl_statusor
pthread
ssl
z
address_sorting
upb
cares
re2
crypto
protobuf
protoc
```

# windows 生成包下载地址

[grpc_vs_2019](https://download.csdn.net/download/xie1xiao1jun/13646650)

更多 : 

[gmsec/cmsec](https://github.com/gmsec/cmsec)

https://github.com/grpc/grpc/blob/master/BUILDING.md