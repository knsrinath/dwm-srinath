# Maintainer: knsrinath <knsrinath2005@gmail.com>
pkgname=dwm-srinath
pkgver=6.2
pkgrel=1
pkgdesc="A heavily-patched and customized build of dwm from Srinath."
arch=(x86_64)
url="https://github.com/knsrinath/dwm.git"
license=('MIT')
groups=()
depends=(libx11 libxinerama ttf-jetbrains-mono freetype2)
makedepends=(make)
checkdepends=()
optdepends=(st dmenu)
provides=(dwm)
conflicts=(dwm)
replaces=()
backup=()
options=()
source=("git+$url")
noextract=()
md5sums=('SKIP')
validpgpkeys=()

pkgver() {
  cd "${_pkgname}"
  printf "6.2" "$(git rev-list --count HEAD)" "$(git rev-parse --short HEAD)"
}

build() {
  cd dwm
  make X11INC=/usr/include/X11 X11LIB=/usr/lib/X11 FREETYPEINC=/usr/include/freetype2
}

package() {
  cd dwm 
  mkdir -p ${pkgdir}/opt/${pkgname}
  cp -rf * ${pkgdir}/opt/${pkgname}
  make PREFIX=/usr DESTDIR="${pkgdir}" install
  install -Dm644 LICENSE "${pkgdir}/usr/share/licenses/dwm/LICENSE"
  install -Dm644 README.org "${pkgdir}/usr/share/doc/dwm/README.md"
}
