load("@rules_cc//cc:defs.bzl", "cc_test", "cc_binary")

cc_test(
    name = "test_serializer",
    srcs = ["test.cpp"],
    deps = [
        "//core/serializer:dvalue_serializer",
        "//core/data:dvalue",
        "@catch2//:catch2_main",
    ],
    size = "small",
)

filegroup(
    name="files",
    srcs=[
        "input.txt",
        "output.txt",
    ],
    tags = [
        "input_files",
        "output_files",
    ],
)

cc_binary(
    name = "debug_serializer",
    srcs = ["main.cpp"],
    deps = [
        "//core/serializer:dvalue_serializer",
    ],
    data = [":files"],
)