{
  description = "klassy";

  inputs = {
    nixpkgs = {
      type = "indirect";
      id = "nixpkgs";
    };

    klassy = {
      type = "git";
      url = "https://github.com/paulmcauley/klassy/";
      flake = false;
      submodules = true;
      ref = "refs/tags/6.2.breeze6.2.1";
    };
  };

  outputs = { self, nixpkgs, klassy }: {
    packages.x86_64-linux.klassy =
      with import nixpkgs { system = "x86_64-linux"; };
      stdenv.mkDerivation {
        makeFlags = [ "PREFIX=$(out)" ];
        name = "klassy";
        src = klassy;
        buildPhase = ''
          sh install.sh
          tree
          exit 1
        '';
        installPhase = ''
          exit 1
        '';

        buildInputs = [
        ];

        nativeBuildInputs = [
          cmake
          kdePackages.extra-cmake-modules
          kdePackages.kcoreaddons
          kdePackages.kcolorscheme
          kdePackages.kconfig
          kdePackages.kguiaddons
          kdePackages.ki18n
          kdePackages.kiconthemes
          kdePackages.kwindowsystem
          kdePackages.qtbase
          kdePackages.wrapQtAppsHook
          qt6.full
        ];
      };

    # Could NOT find kcoreaddons (missing: KF6CoreAddons_DIR)
    # Could NOT find kcolorscheme (missing: KF6ColorScheme_DIR)
    # Could NOT find kconfig (missing: KF6Config_DIR)
    # Could NOT find kguiaddons (missing: KF6GuiAddons_DIR)
    # Could NOT find ki18n (missing: KF6I18n_DIR)
    # Could NOT find kiconthemes (missing: KF6IconThemes_DIR)
    # Could NOT find kwindowsystem (missing: KF6WindowSystem_DIR)

    packages.x86_64-linux.default = self.packages.x86_64-linux.klassy;
    defaultPackage.x86_64-linux = self.packages.x86_64-linux.klassy;

  };
}
