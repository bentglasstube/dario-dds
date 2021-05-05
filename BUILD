package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "dario-dds",
    data = ["//content"],
    linkopts = [
        "-lSDL2",
        "-lSDL2_image",
        "-lSDL2_mixer",
    ],
    srcs = ["main.cc"],
    deps = [
        ":game",
        ":screens",
    ],
)

# Basic framework objects

cc_library(
    name = "audio",
    srcs = ["audio.cc"],
    hdrs = ["audio.h"],
)

cc_library(
    name = "graphics",
    srcs = ["graphics.cc"],
    hdrs = ["graphics.h"],
)

cc_library(
    name = "input",
    srcs = ["input.cc"],
    hdrs = ["input.h"],
)

cc_library(
    name = "screen",
    srcs = ["screen.cc"],
    hdrs = ["screen.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
    ]
)

cc_library(
    name = "game",
    srcs = ["game.cc"],
    hdrs = ["game.h"],
    deps = [
        ":audio",
        ":graphics",
        ":input",
        ":screen",
        ":screens",
        ":text",
    ],
)

# Graphical objects

cc_library(
    name = "backdrop",
    srcs = ["backdrop.cc"],
    hdrs = ["backdrop.h"],
    deps = [":graphics"],
)

cc_library(
    name = "box",
    srcs = ["box.cc"],
    hdrs = ["box.h"],
    deps = [":graphics"],
)

cc_library(
    name = "floating_text",
    srcs = ["floating_text.cc"],
    hdrs = ["floating_text.h"],
    deps = [":text"],
)

cc_library(
    name = "sprite",
    srcs = ["sprite.cc"],
    hdrs = ["sprite.h"],
    deps = [":graphics"],
)

cc_library(
    name = "text",
    srcs = ["text.cc"],
    hdrs = ["text.h"],
    deps = [":graphics"],
)

cc_library(
    name = "screens",
    srcs = [
        "main_screen.cc",
        "settings_screen.cc",
        "title_screen.cc",
    ],
    hdrs = [
        "main_screen.h",
        "settings_screen.h",
        "title_screen.h",
    ],
    deps = [
        ":backdrop",
        ":box",
        ":crumble",
        ":face",
        ":game_grid",
        ":menu",
        ":screen",
        ":settings",
        ":sprite",
        ":text",
    ],
)

cc_library(
    name = "candy",
    srcs = ["candy.cc"],
    hdrs = ["candy.h"],
    deps = [":grid_piece"],
)

cc_library(
    name = "candy_block",
    srcs = ["candy_block.cc"],
    hdrs = ["candy_block.h"],
    deps = [":candy"],
)

cc_library(
    name = "crumble",
    srcs = ["crumble.cc"],
    hdrs = ["crumble.h"],
    deps = [":sprite"],
)

cc_library(
    name = "face",
    srcs = ["face.cc"],
    hdrs = ["face.h"],
    deps = [":graphics"],
)

cc_library(
    name = "game_grid",
    srcs = ["game_grid.cc"],
    hdrs = ["game_grid.h"],
    deps = [
        ":audio",
        ":candy_block",
        ":crumble",
        ":floating_text",
        ":input",
        ":tooth",
    ],
)

cc_library(
    name = "grid_piece",
    srcs = ["grid_piece.cc"],
    hdrs = ["grid_piece.h"],
    deps = [":graphics"],
)

cc_library(
    name = "menu",
    srcs = ["menu.cc"],
    hdrs = ["menu.h"],
    deps = [
        ":text",
        ":tooth_sprite",
    ],
)

cc_library(
    name = "settings",
    hdrs = ["settings.h"],
)

cc_library(
    name = "tooth",
    srcs = ["tooth.cc"],
    hdrs = ["tooth.h"],
    deps = [":grid_piece"],
)

cc_library(
    name = "tooth_sprite",
    srcs = ["tooth_sprite.cc"],
    hdrs = ["tooth_sprite.h"],
    deps = [":sprite"],
)

