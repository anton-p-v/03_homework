load("@rules_pkg//pkg:tar.bzl", "pkg_tar")
load("@rules_pkg//pkg:deb.bzl", "pkg_deb")

cc_binary(
    name = "homework",
    srcs = [
        "main.cpp",
    ],
    deps = [
        "//src/version",
        "//src/factorial",
    ],
)

pkg_tar(
    name = "homework_tar",
    srcs = [":homework"],
    package_dir = "/usr/bin",
    package_file_name = "homework.tar",
)

pkg_deb(
    name = "homework_deb",
    data = ":homework_tar",
    description = "03_homework for otus",
    maintainer = "antonplatonov@yandex-team.ru",
    package = "homework",
    package_file_name = "homework-0.0.$(VERSION)-Linux.deb",
    version = "1.0",
)
