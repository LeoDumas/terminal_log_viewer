{
  description = "C++ Pointer & Borrowing Lab";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    system = "x86_64-linux";
    pkgs = nixpkgs.legacyPackages.${system};
  in {
    devShells.${system}.default = pkgs.mkShell {
      buildInputs = with pkgs; [
        gcc
        libgcc
        gdb
        valgrind
        cmake
        python314
      ];

      shellHook = ''
        echo "C++ environnement"
        echo "'g++ main.cpp -o <app>' to compile."
      '';
    };
  };
}
