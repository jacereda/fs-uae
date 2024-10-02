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
      pkgs = import nixpkgs {
        inherit system;
        overlays = [];
      };
      spkgs = import nixpkgs {
        inherit system;
        overlays = [
          (self: super: {

            portimidi = super.portmidi.overrideAttrs (p: {
              postInstall = "";
            });

            SDL2 = (super.SDL2.override {
              alsaSupport = false;
              dbusSupport = false;
              udevSupport = false;
              libdecorSupport = false;
              pipewireSupport = false;
              pulseaudioSupport = false;
            }).overrideAttrs (p: {
              postFixup = "";
            });

          })
        ];
      };
    in rec {
      packages.default = spkgs.callPackage ./default.nix {};
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
