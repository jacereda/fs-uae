{ pkgs ? import <nixpkgs> {}
}:

pkgs.stdenv.mkDerivation {
  pname = "fs-uae";
  version = "tbd";

  src = ./.;

  configureFlags = [];

  enableParallelBuilding = true;

  hardeningDisable = [ "all" ];

  nativeBuildInputs = with pkgs; [
    autoreconfHook
    bear
    enet
    gdb
    git
    xorg.makedepend
    pkg-config
    zip
  ];

  buildInputs = with pkgs; [
    flac
    glib
    libmpeg2
    libpng
    portmidi
    SDL2
    SDL2_ttf
    freetype
    udis86
    xorg.libXcursor
    xorg.libXxf86vm
    xorg.libX11
    xorg.libXext
    xorg.libXi
  ];

  meta = with pkgs.lib; {
    homepage = "https://github.com/jacereda/fs-uae";
    description = ''
    Amiga emulator based on UAE/WinUAE, with a focus on emulating games.
    '';
    licencse = licenses.gpl2;
    platforms = with platforms; linux ++ darwin;
  };
}
