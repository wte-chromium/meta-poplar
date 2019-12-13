require kernel-module-mali-midgard.inc

SRC_URI += "file://0001-hi3798cv200-support.patch"

MALI_PACKAGE_NAME = "TX011-SW-99002-${PV}"

SRC_URI[driver.md5sum] = "3b0c67ff1cd148aca16113f216bf5ebb"
SRC_URI[driver.sha256sum] = "005ad55aaee31c518bb16f7a0a4f207e82ab8f1c82e436356420f393d1bb18cb"

COMPATIBLE_MACHINE = "poplar"
