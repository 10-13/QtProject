load("@rules_qt//:qt.bzl", "qt_cc_binary", "qt_cc_library", "qt_resource", "qt_resource_via_qrc", "qt_ui_library")

qt_ui_library(
    name = "main_window_ui",
    ui = "mainwindow.ui",
    deps = [
        "@rules_qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "main_window",
    srcs = [
        "main_window.cpp",
    ],
    hdrs = ["main_window.h"],
    deps = [
        ":main_window_ui",
        "@rules_qt//:qt_widgets",
    ],
)

qt_cc_binary(
    name = "main",
    srcs = ["main.cpp"],
    deps = [
        ":main_window",
        "@rules_qt//:qt_core",
        "@rules_qt//:qt_qml",
        "@rules_qt//:qt_widgets",
    ],
)