# SPDX-FileCopyrightText: 2022 Ignacy Kajdan <ignacy.kajdan@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

add_library(plasma_potd_lychee MODULE lycheeprovider.cpp)

target_link_libraries(plasma_potd_lychee
  Plasma::PotdProvider
  KF5::KIOCore
)

install(TARGETS plasma_potd_lychee DESTINATION ${KDE_INSTALL_PLUGINDIR}/potd)
