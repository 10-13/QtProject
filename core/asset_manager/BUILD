load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary")

cc_library(
    name="asset_manager",
    hdrs=["AssetManager.h"],
    deps=[
        "//core/includes:def_includes",
    ],
    visibility=[
        "//visibility:public",
    ],
)

# ----- testing ----- 
cc_binary(
    name="debug",
    srcs=["test.cpp"],
    deps=[":asset_manager"],
)