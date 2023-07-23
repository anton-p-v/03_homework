# 03_homework


build:
```
bazel build --cxxopt=-std=c++14 //src:homework --define VERSION=1
```

run:
```
bazel-bin/src/homework
```

build deb package:
```
bazel build --cxxopt=-std=c++14 //src:homework_deb --define VERSION=1
```
