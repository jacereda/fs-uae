{
  inputs = {
    # nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem
      (system:
        let pkgs = import nixpkgs {
            inherit system;
            };
            spkgs = (import nixpkgs {
            inherit system;
                }).pkgsStatic;
        in
          {
            devShells.default = pkgs.mkShell {
              hardeningDisable = [ "all" ];
              nativeBuildInputs = with pkgs; [
                autoconf
                automake
                # bison
                # binutils
                # expat
                # flex
                # gettext
                git
                glib
                # gmp
                # gperf
                # lhasa
                # libmpc
                libmpeg2
                libpng
                xorg.makedepend
                # mpfr
                # ncurses
                # patch
                # pcre2
                # perlPackages.PodSimple
                pkg-config
                # readline
                # rsync
                SDL2
                SDL2_ttf
                # harfbuzz
                freetype
                # texinfo
                # wget
                zip
                xorg.libXcursor
                xorg.libXxf86vm
                xorg.libX11
                xorg.libXext
                xorg.libXi

              ];
            };
          }
      );
}
