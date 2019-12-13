SUMMARY = "${MACHINE} partitions files"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
PR = "${SRCDATE}"
PACKAGE_ARCH = "${MACHINE_ARCH}"

inherit deploy

SRC_URI = "file://${MACHINE}-recovery-${SRCDATE}.zip"

S = "${WORKDIR}"

ALLOW_EMPTY_${PN} = "1"
do_configure[nostamp] = "1"

do_deploy() {
    install -d ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/recovery-${MACHINE}.bin ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/pq_param.bin ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/baseparam.img ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/fastboot.bin ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/logo.img ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/bootargs.bin ${DEPLOY_DIR_IMAGE}/poplar-partitions/${MACHINE}
    install -m 0755 ${WORKDIR}/${MACHINE}/update_bootargs_${MACHINE}.bin ${DEPLOY_DIR_IMAGE}/poplar-partitions
}

addtask deploy before do_build after do_install

INSANE_SKIP_${PN} += "already-stripped"
