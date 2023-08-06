# 03_homework


build:
```
bazel build --cxxopt=-std=c++14 //src:homework --define VERSION=1
```

run:
```
bazel-bin/src/homework
```

run tests:
```
bazel test --cxxopt=-std=c++14 --test_output=all //src/factorial:factorial_test
```

build deb package:
```
bazel build --cxxopt=-std=c++14 //src:homework_deb --define VERSION=1
```
