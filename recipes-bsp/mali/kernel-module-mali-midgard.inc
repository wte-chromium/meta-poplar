inherit module

SUMMARY = "Open Source Mali Utgard GPU Kernel Drivers"
SRC_URI = "https://developer.arm.com/-/media/Files/downloads/mali-drivers/kernel/mali-midgard-gpu/${MALI_PACKAGE_NAME}.tgz;name=driver"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://driver/product/kernel/license.txt;md5=13e14ae1bd7ad5bff731bba4a31bb510"

EXTRA_OEMAKE ?= ""

S = "${WORKDIR}/${MALI_PACKAGE_NAME}/"

do_compile() {
	oe_runmake -C ${STAGING_KERNEL_DIR} \
		M=$(pwd)/driver/product/kernel \
		O=${STAGING_KERNEL_BUILDDIR} \
		EXTRA_CFLAGS="${MALI_FLAGS}" \
		${MALI_KCONFIG}
}

do_install() {
	oe_runmake -C ${STAGING_KERNEL_DIR} \
		M=$(pwd)/driver/product/kernel \
		INSTALL_MOD_PATH="${D}" \
		O=${STAGING_KERNEL_BUILDDIR} \
		EXTRA_CFLAGS="${MALI_FLAGS}" \
		${MALI_KCONFIG} \
		modules_install
}

do_install_append() {
	install -d ${D}${sysconfdir}/modules-load.d
	echo mali > ${D}${sysconfdir}/modules-load.d/mali.conf
}

FILES_${PN} += "${sysconfdir}/modules-load.d/_mali.conf"

python() {
	config = ["CONFIG_MALI_MIDGARD=m",
		"CONFIG_MALI_DEBUG=y",
		"CONFIG_MALI_PLATFORM_DEVICETREE=y",
		"CONFIG_MALI_TRACE_TIMELINE=y",
		"CONFIG_MALI_GATOR_SUPPORT=y",
		"CONFIG_MALI_DEVFREQ=y"]

	for c in config:
		d.appendVar('MALI_FLAGS', '-D' + c + ' ')
		d.appendVar('MALI_KCONFIG', c + ' ')
}
