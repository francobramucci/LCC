{ pkgs ? import <nixpkgs> {} }:

pkgs.mkShell {
  packages = [
    (pkgs.haskellPackages.ghcWithPackages (hp: with hp; [
      gloss
    ]))
    pkgs.cabal-install
  ];

  shellHook = ''
    export LD_LIBRARY_PATH="${pkgs.lib.makeLibraryPath (with pkgs; [
      libGL
      freeglut
      # Librerías nativas de Wayland
      wayland
      libxkbcommon
      # Dependencias de respaldo para XWayland (requeridas por FreeGLUT)
      xorg.libX11
      xorg.libXrandr
      xorg.libXi
      xorg.libXcursor
    ])}:$LD_LIBRARY_PATH"
  '';
}
