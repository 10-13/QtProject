load("@rules_cc//cc:defs.bzl", "cc_test")

cc_test(
    name = "test_serializer",
    srcs = ["test.cpp"],
    deps = [
        "//core/serializer:dvalue_serializer",
        "@catch2//:catch2_main",
    ],
    size = "small",
)