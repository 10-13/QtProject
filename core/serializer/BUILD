load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "dvalue_serializer",
    srcs = ["DValueSerializer.cpp"],
    hdrs = ["DValueSerializer.h"],
    deps = [ 
        "//core/includes:def_includes",
        "//core/data:dvalue",
    ],
    visibility = [
        "//visibility:public",
    ],
)