{
  description = "Flake for FS-UAE.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system: let
    pkgs = import nixpkgs {
      inherit system;
      overlays = [];
    };
    spkgs = pkgs; # .pkgsStatic
    sdl2 = (spkgs.SDL2.override {
      withStatic = true;
      alsaSupport = false;
      dbusSupport = false;
      udevSupport = false;
      libdecorSupport = false;
      pipewireSupport = false;
      pulseaudioSupport = false;
      libGL = pkgs.libGL;
    }).overrideAttrs (p: {
      postFixup = "";
    });
    grph = (spkgs.graphite2.override {
      static = true;
    }).overrideAttrs (p: {
      doCheck = false;
    });
    hb = spkgs.harfbuzz.override {
      graphite2 = grph;
    };
    sdl2ttf = (spkgs.SDL2_ttf.override {
      SDL2 = sdl2;
      freetype = spkgs.freetype;
      harfbuzz = hb;
      libGL = pkgs.libGL;
      enableSdltest = false;
    }).overrideAttrs (p: {
      configureFlags = p.configureFlags ++ [ "--enable-static" "--disable-shared" ];
    });
    pm = (spkgs.portmidi.override {
      alsa-lib = spkgs.alsa-lib;
    }).overrideAttrs (p: {
        postInstall = "";
    });
  in rec {
    packages.default = pkgs.callPackage ./default.nix {
      # SDL2 = sdl2;
      # alsa-lib = spkgs.alsa-lib;
      # SDL2_ttf = sdl2ttf;
      # # SDL2_ttf = null;
      # flac = spkgs.flac;
      # freetype = spkgs.freetype;
      # glib = spkgs.glib;
      # libmpeg2 = spkgs.libmpeg2;
      # libogg = spkgs.libogg;
      # libpng = spkgs.libpng;
      # portmidi = pm;
      # udis86 = spkgs.udis86;
    };
    devShells.default = pkgs.mkShell {
      nativeBuildInputs = packages.default.nativeBuildInputs ++ (with pkgs; [
        bear
        gdb
        git
      ]);
      buildInputs = packages.default.buildInputs;
    };
  });
}
