load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name="asset_manager",
    hdrs=["AssetManager.h"],
    deps=[
        "//core/includes:def_includes",
        "//core/data:dvalue",
        "@nlohmann_json//:json",
    ],
    visibility=[
        "//visibility:public",
    ],
)