load("@rules_cc//cc:defs.bzl", "cc_binary")

filegroup(
    name="json_files",
    srcs=[
        "input.json",
        "output.json",
        "text.txt",
    ],
    tags = [
        "input_files",
        "output_files",
    ],
)

cc_binary(
    name="debug",
    srcs=["test.cpp"],
    data=["json_files"],
    deps=["//core/asset_manager:asset_manager"],
)