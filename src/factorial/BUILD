cc_library(
    name = "factorial",
    hdrs = ["factorial.h"],
    srcs = ["factorial.cpp"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "factorial_test",
    size = "small",
    srcs = [
        "factorial_test.cpp",
    ],
    deps = [
        "@googletest//:gtest_main",
        ":factorial",
    ],
)
