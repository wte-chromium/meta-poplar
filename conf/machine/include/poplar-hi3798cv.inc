MACHINE_KERNEL_PR = "r0"
KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

PREFERRED_VERSION_linux-poplar = "4.4.35"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-poplar"
PREFERRED_PROVIDER_virtual/egl ?= "poplar-mali"
PREFERRED_PROVIDER_virtual/libgles1 ?= "poplar-mali"
PREFERRED_PROVIDER_virtual/libgles2 ?= "poplar-mali"
PREFERRED_PROVIDER_virtual/libgbm ?= "poplar-mali"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "poplar-dvb-modules"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "poplar-dvb-modules"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/poplar-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Kodi
EXTRA_OECONF_append_pn-kodi += " --with-gpu=mali --enable-player=hiplayer"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm  --with-eac3 --with-amr --with-spark"

MACHINE_EXTRA_RRECOMMENDS = " \
	ffmpeg \
	ntfs-3g \
"

MACHINE_FEATURES += " alsa usbhost wlan 3dtv switchoff osdposition hdmicec"

IMAGEVERSION := "${DISTRO_NAME}-${DISTRO_VERSION}-${DATE}"
IMAGEVERSION[vardepsexclude] = "DATE"
IMAGEDIR ?= "poplar"
IMAGEDIRRECOVERY ?= "poplar-recovery"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_poplarfastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.tar; \
	echo "${IMAGEVERSION}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/imageversion; \
	echo "${IMAGEVERSION}_emmc.zip" > ${IMGDEPLOYDIR}/${IMAGEDIR}/unforce_${MACHINE}.txt; \
	echo "Rename the unforce_${MACHINE}.txt to force_${MACHINE}.txt and move it to the root of your usb-stick" > ${IMGDEPLOYDIR}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	echo "When you enter the recovery menu then it will force to install the image ${IMAGEVERSION}_emmc.zip in the image-slot1" >> ${IMGDEPLOYDIR}/${IMAGEDIR}/force_${MACHINE}_READ.ME; \
	cp ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootoptions.img; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/update_bootargs_${MACHINE}.bin; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/logo.img; \
	cp ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}/recovery-${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/recovery.bin; \
	echo "To access the recovery image press immediately by power-up the frontpanel button or hold down a remote button key untill the display says boot" > ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/recovery.txt; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_recovery_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIRRECOVERY}; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${DISTRO_NAME}-${DISTRO_VERSION}-${MACHINE}_emmc.zip unforce_${MACHINE}.txt force_${MACHINE}_READ.ME ${MACHINE}/imageversion ${MACHINE}/uImage ${MACHINE}/rootfs.tar.bz2; \
	cd ..; \
	rm -Rf ${IMAGEDIR}; \
"
