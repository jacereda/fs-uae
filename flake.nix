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
  in rec {
    packages.default = pkgs.callPackage ./default.nix {};
    devShells.default = pkgs.mkShell {
      nativeBuildInputs = packages.default.nativeBuildInputs;
      buildInputs = packages.default.buildInputs;
    };
  });
}
