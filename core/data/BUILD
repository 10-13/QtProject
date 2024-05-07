load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name="dvalue",
    hdrs=["DValue.h"],
    deps=[
        "//core/includes:def_includes",
    ],
    visibility=[
        "//visibility:public",
    ],
)

cc_library(
    name="dvrequire",
    hdrs=[
        "DVRequire.h",
        "DVGlobalRequirements.h",
        "DVReqMacro.h"
    ],
    deps=[
        ":dvalue",
    ],
    visibility=[
        "//visibility:public",
    ],
)