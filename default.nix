
{ lib
, SDL2
, SDL2_ttf
, autoreconfHook
, flac
, freetype
, glib
, libX11
, libXcursor
, libXext
, libXi
, libXxf86vm
, libmpeg2
, libpng
, pkg-config
, portmidi
, stdenv
, strip-nondeterminism
, udis86
, zip
}:

stdenv.mkDerivation {
  pname = "fs-uae";
  version = "5.3.0pre";

  src = ./.;

  configureFlags = [];

  enableParallelBuilding = true;

  hardeningDisable = [ "all" ];

  nativeBuildInputs = [
    autoreconfHook
    pkg-config
    strip-nondeterminism
    zip
  ];

  buildInputs = [
    SDL2
    SDL2_ttf
    flac
    freetype
    glib
    libX11
    libXcursor
    libXext
    libXi
    libXxf86vm
    libmpeg2
    libpng
    portmidi
    udis86
  ];

  strictDeps = true;

  postFixup = ''
    strip-nondeterminism --type zip $out/share/fs-uae/fs-uae.dat
  '';

  meta = with lib; {
    homepage = "https://github.com/jacereda/fs-uae";
    description = "Accurate, customizable Amiga Emulator";
    longDescription = ''
      FS-UAE integrates the most accurate Amiga emulation code available from
      WinUAE. FS-UAE emulates A500, A500+, A600, A1200, A1000, A3000 and A4000
      models, but you can tweak the hardware configuration and create customized
      Amigas.
    '';
    licencse = licenses.gpl2Plus;
    platforms = with platforms; linux ++ darwin;
  };
}
