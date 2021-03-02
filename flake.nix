{
  description = "recut-pipeline";
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/733e537a8ad76fd355b6f501127f7d0eb8861775";
    mcp3d.url = "git+ssh://git@github.com/muyezhu/mcp3d?ref=stable_lib";
    #mcp3d.url = "git+ssh://git@github.com/muyezhu/mcp3d?ref=kdm-dev";
    mcp3d.inputs.nixpkgs.follows = "nixpkgs";
    # alternatively you could pin a certain commit like:
    # mcp3d.url = "git+ssh://git@github.com/muyezhu/mcp3d?ref=kdm-dev&rev=<commit hash>";
    # or you could use your local filesystem branch with:
    # mcp3d.url = "/home/kdmarrett/mcp3d";
  };

  outputs = inputs: {

    defaultPackage.x86_64-linux = import ./recut.nix {
      nixpkgs = inputs.nixpkgs;
      mcp3d = inputs.mcp3d;
    };
  };
}
