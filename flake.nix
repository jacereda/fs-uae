{
  description = "Flake for FS-UAE.";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
    utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, ... }@inputs: inputs.utils.lib.eachSystem [
    "x86_64-linux" "i686-linux" "aarch64-linux" "x86_64-darwin"
  ] (system:
    let
      opkgs = (import nixpkgs {
        inherit system;
      });

      overlay = (self: super: {
        libGL=opkgs.libGL;

        # portimidi = null;
        portmidi = super.portmidi.overrideAttrs (p: {
          postInstall = "";
        });

        SDL2_ttf = null;


        SDL2 = opkgs.SDL2;
        # SDL2 = (super.SDL2.override {
        #   x11Support = true;
        #   withStatic = true;
        #   openglSupport = true;
        #   waylandSupport = true;
        #   alsaSupport = true;
        #   dbusSupport = false;
        #   udevSupport = false;
        #   libdecorSupport = false;
        #   pipewireSupport = false;
        #   pulseaudioSupport = false;
        # }).overrideAttrs (p: {
        #   postFixup = "";
        #   # configureFlags = p.configureFlags ++ [ "--enable-x11" "--enable-wayland" ];
        # });
        # SDL2 = null;

      });
      # xpkgs = (import nixpkgs {
      #   inherit system;
      #   overlays = [ overlay ];
      #   crossOverlays = [ overlay ];
      # });
      pkgs = (import nixpkgs {
        inherit system;
        overlays = [ overlay ];
      });
      mpkgs = pkgs.pkgsCross.musl64;
      spkgs = pkgs.pkgsStatic;
      nstdenv = pkgs.clangStdenv;
      sstdenv = pkgs.clangStdenv;
    in rec {
      packages.default = pkgs.callPackage ./default.nix {};
      packages.musl64 = mpkgs.callPackage ./default.nix {};
      packages.static = spkgs.callPackage ./default.nix {
        stdenv = sstdenv;
        autoreconfHook = pkgs.autoreconfHook;
        pkg-config = pkgs.pkg-config;
        strip-nondeterminism = pkgs.strip-nondeterminism;
        zip = pkgs.zip;
      };
      devShells.default = (pkgs.mkShell.override {stdenv = nstdenv;}) {
        nativeBuildInputs = packages.default.nativeBuildInputs ++ (with pkgs; [
          bear
          gdb
          git
          tracy
        ]);
        buildInputs = packages.default.buildInputs;
      };
      devShells.static = (spkgs.mkShell.override {stdenv = sstdenv;}) {
        nativeBuildInputs = packages.static.nativeBuildInputs ++ (with pkgs; [
          bear
          gdb
          git
          tracy
        ]);
        buildInputs = packages.static.buildInputs;
      };
    });
}
