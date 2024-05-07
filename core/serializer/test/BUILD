load("@rules_cc//cc:defs.bzl", "cc_test")

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


cc_test(
    name = "test_serializer",
    srcs = ["test.cpp"],
    data = [":files"],
    deps = [
        "//core/serializer:dvalue_serializer",
        "@catch2//:catch2_main",
    ],
    size = "small",
)