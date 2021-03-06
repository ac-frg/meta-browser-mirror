# Copyright (C) 2009-2013, O.S. Systems Software Ltda. All Rights Reserved
# Released under the MIT license (see packages/COPYING)

DEPENDS = "mozilla-devscripts-native"
RDEPENDS = "firefox"

LICENSE = "MPLv1 | GPLv2+ | LGPLv2.1+"

# Ugly hack for now; we need to check license per recipe later
LIC_FILES_CHKSUM = "file://${COREBASE}/LICENSE;md5=3f40d7994397109285ec7b81fdeb3b58"

LANGUAGE = "${@get_language_name('${PN}')}"
INC_PR = "r2"

# Mangle place where to store the file
DL_DIR_append = "/${PN}-${PV}"

SRC_URI = "ftp://ftp.mozilla.org/pub/mozilla.org/mozilla.org/firefox/releases/${PV}/linux-i686/xpi/${LANGUAGE}.xpi"
S = "${WORKDIR}"

inherit allarch

def get_language_name(package):
    lang = package.replace('firefox-l10n-', '')
    if lang.find('-') != -1:
        lang = lang.split('-')
        lang[1] = lang[1].upper()
        lang = '-'.join(lang)

    return lang

do_configure() {
    xpi-unpack ${LANGUAGE}.xpi ${LANGUAGE}
}

do_install() {
    EXTENSION=`sed --posix '/em:id=/!d;s/[ ]*em:id="//;s/".*//' ${LANGUAGE}/install.rdf`

    xpi-pack ${LANGUAGE} ${EXTENSION}.xpi

    mkdir -p ${D}${libdir}/firefox/extensions/
    install -m 0644 ${EXTENSION}.xpi ${D}${libdir}/firefox/extensions/${EXTENSION}.xpi
}

FILES_${PN} += "${libdir}/firefox"
