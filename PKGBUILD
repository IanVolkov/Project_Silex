# Maintainer: Your Name <your.email@example.com>
pkgname=particle-simulation
pkgver=1.0
pkgrel=1
pkgdesc="A 2D particle physics simulation optimized for Arch Linux"
arch=('x86_64')
url="https://github.com/IanVolkov/Project_Silex"
license=('custom')
depends=('sdl2' 'sdl2_ttf')
makedepends=('gcc' 'make')
source=()
sha256sums=()

build() {
    cd "$srcdir"
    make
}

package() {
    cd "$srcdir"
    install -Dm755 particle_simulation "$pkgdir/usr/bin/particle_simulation"
    install -Dm644 Parameters.txt "$pkgdir/usr/share/particle_simulation/Parameters.txt"
    install -Dm644 README.md "$pkgdir/usr/share/doc/$pkgname/README.md"
}
