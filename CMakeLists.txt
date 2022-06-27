# SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.16)

project(lychee-potd-provider VERSION 0.1.0)

# Set the compiler standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set minimum versions of frameworks
set(QT5_MIN_VERSION 5.15.0)
set(KF5_MIN_VERSION 5.77.0)

find_package(ECM "${KF5_MIN_VERSION}" REQUIRED NO_MODULE)

# Append ECM to the module path
list(APPEND CMAKE_MODULE_PATH "${ECM_MODULE_PATH}")

find_package(Qt5 "${QT5_MIN_VERSION}" CONFIG REQUIRED COMPONENTS Core)
find_package(KF5 "${KF5_MIN_VERSION}" REQUIRED COMPONENTS KIO)
find_package(PlasmaPotdProvider CONFIG REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDEClangFormat)
include(KDEGitCommitHooks)
include(ECMUninstallTarget)

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
