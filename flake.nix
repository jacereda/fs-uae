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
                bear
                enet
                flac
                gdb
                git
                glib
                libmpeg2
                libpng
                xorg.makedepend
                pkg-config
                portmidi
                SDL2
                SDL2_ttf
                freetype
                udis86
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
